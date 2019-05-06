#include "project.h"
#include "screen.h"
#include "font.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "strings.h"
#include "settings.h"
#include "stdio.h"
#include "stdlib.h"
#include <FS.h>
#include <Global.h>
#include "sd.h"
#include "uifunctions.h"

#define VDAC_G_B_MAX    255 //Max VDAC code for the Gate/Base 
#define VDAC_D_C_P_MAX  250 //Max VDAC for the Drain/Common
#define VDS_NMOS_LENGTH ((VDAC_D_C_MAX/VD_STEP_NMOS) + 1)
#define VCE_NPN_LENGTH  ((VDAC_D_C_MAX/VC_STEP_NPN) + 1)
#define VDS_PMOS_LENGTH ((VDAC_D_C_MAX/VD_STEP_PMOS) + 1)
#define VCE_PNP_LENGTH  ((VDAC_D_C_MAX/VC_STEP_PNP) + 1)
#define VDAC_N_1_VOLT   21
#define VDAC_P_1_VOLT   229
#define VDAC_G_1_VOLT   63
#define ADC_GAIN        52.0
#define P_SOURCE_VOLTAGE 12


//The lengths of Drain or Common testing points

void set_transistor_test_type(unsigned char device_selection)
{
    if(device_selection < 2)
    {
        AMux_1_Select(0);
        AMux_2_Select(0);
        AMux_3_Select(0);
    }
    else
    {
        AMux_1_Select(1);
        AMux_2_Select(1);
        AMux_3_Select(1);
    }
}
//Conducts a test for a singular Vds and Vgs
double single_test(unsigned char Vds, unsigned char Vgs)
{
    ADC_SAR_1_Wakeup();
    double Output;
    double Output_avg;
    int i;
    VDAC8_DS_SetValue(Vds);
    VDAC8_GS_SetValue(Vgs);
    CyDelay(SETTLING_WAIT_TIME);
    ADC_SAR_1_StartConvert();
    ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
	//waiting until conversion is over
    ADC_SAR_1_StopConvert();
    Output = (ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16())/ADC_GAIN);
    ADC_SAR_1_Sleep();
    if(cooldown_time)
    {
        VDAC8_DS_SetValue(0);
        VDAC8_GS_SetValue(0);
        CyDelay(cooldown_time*SETTLING_WAIT_TIME);
    }
    return Output;
}

double single_test_preset_vds(unsigned char Vgs)
{
    double Output;
    
    ADC_SAR_1_Wakeup();
    VDAC8_GS_SetValue(Vgs);
    CyDelay(SETTLING_WAIT_TIME);
    ADC_SAR_1_StartConvert();
    ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
	//waiting until conversion is over
    ADC_SAR_1_StopConvert();
    Output = (ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16())/ADC_GAIN);
    ADC_SAR_1_Sleep();
    return Output;
}
    

//Finds Vth (The minimum Vgs needed to turn the transistor by sorting through Vgs's until 
//a minumum current of 1 mA is found Id is found by a 1 Ohm series resistor whose potential 
//difference is magnitifed 100 fold for accurate reading
int vgs_th_find(unsigned char Vgs_max, unsigned char Vgs_min ,unsigned char Vds)
{
    //63,255,229
    unsigned char   Vgs;           
	//The Gate-Drain Voltage difference | Vds_real = Vds/256 * 4.096 * 3 (OpAmp gain)
    double          Id=0;         
	//The Drain Current | Id_real = Id/100
    int i;
    VDAC8_DS_SetValue(Vds); //Set Vds to 1 Volt
    VDAC8_GS_SetValue(0);
    for(Vgs = Vgs_min; Vgs < Vgs_max; Vgs++)
    {
        Id = single_test_preset_vds(Vgs);
        
        if(Id > ID_TH)
        {
            //Once Id > 1 mV transistor is "on" and we can return Vgs as Vth
            return Vgs;
        }
    }
    return 0;
}

//Finds the MAX current 20mA, Id is found through a 100 Ohm series resistor
//Sweeps through Vgs until a max current of 20 mA is found
//Therefor ID_MAX = 20*100 == 2000
unsigned int vgs_max_id_find(unsigned char Vth, unsigned char Vds_max)
{
    unsigned char   Vgs;
	//The Gate-Source Voltage difference | Vgs_real = Vgs/256 * 4.096
    double          Id=0.0; 
	//The Drain Current | Id_real = Id/100
    VDAC8_DS_SetValue(Vds_max);
	//Sets Vds = 188/256 * 4.096 * 3 = 9V (max Vds to test wtih) to find max current
    
    for(Vgs = Vth; Vgs < 255; Vgs++)
    {            
        
        Id = single_test_preset_vds(Vgs);
        
        if (Id >= ID_MAX)
        {
            VDAC8_DS_SetValue(0);
            VDAC8_GS_SetValue(0);
            return Vgs-1; //Stop stepping once max current is hit
        }
    }
    
    

    return Vgs; //Returns the previous Vgs step to avoid going past 20mA
}

//This function runs the main test, it intakes the y_max used to calculate the
//pixels for line segments and the Vgs test points
int run_test(int y_max, unsigned char Vgs_test_points[curve_nums],double Vgs_double[curve_nums], unsigned char device_selection, int SD_files_written)
{
    int i,j,k;
    double Id;
    double Id_avg;
    char print_string[20];
    char file_name[11]="data";
    char SD_files_written_str[3];
    int y_pixel_prev, x_pixel_prev;
    int y_pixel, x_pixel;
    int curve_color[CURVE_NUM_MAX] = {BLUE, GREEN, RED, ORANGE, CYAN, PINK};
    
    for(i = 0; i < curve_nums; i++)
    {
        if(write_sd==1)
        {
            sprintf(SD_files_written_str,"%d",SD_files_written);
            strcat(file_name,SD_files_written_str);
            strcat(file_name,".txt");
            write_header_info(file_name,device_selection,i,Vgs_double);
        }
        //ADC_SAR_1_Wakeup();//wakeup from sleep for reset purposes
        for(j = 0; j < vds_high_vdac_code; j++)
        {
            if(/*!screen_state*/ screen_state != PLOT_SCREEN)
            {
                return 0;   
            }
            Id_avg = 0.0;//reset Id Value
            //Averaging multiple tests to elminate noise
            for(k=0; k<num_avg; k++)
            {
                if(device_selection < 2) //if testing N-Type Devices
                {
                    Id_avg += single_test(j,Vgs_test_points[i]);
                } else //if testing P-Type devices
                {
                    Id_avg += single_test(vds_high_vdac_code - j, Vgs_double[i]);
                }
            }
            Id_avg /= num_avg;
            if(write_sd==1)
            {
                write_data(file_name,Id_avg,j,device_selection);//update CSV File with new Id/Ic
            }
            //creating pixel coordinates via rations (Id/Id_max == y_pixel/y_resolution)
            y_pixel = (int) ((Id_avg*Y_RES*0.8)/(y_max));
            x_pixel = (int) (VDAC_D_C_P_MAX * j)/vds_high_vdac_code;
            if (j > 0) //only draw a line if 2 points have been tested already
            {
                draw_line(x_pixel_prev+30,y_pixel_prev+10,x_pixel+30,y_pixel+10,curve_color[i]);
            }
            y_pixel_prev = y_pixel;
            x_pixel_prev = x_pixel;
        }
        switch(device_selection)
        {
            case 0:
                sprintf(print_string,"%5.3f V",Vgs_double[i]);
                break;
            case 1:
                sprintf(print_string,"%.3f MA",Vgs_double[i]);
                break;
            case 2:
                sprintf(print_string,"%6.3f V",Vgs_double[i]);
                break;
            case 3:
                sprintf(print_string,"%6.3f MA",Vgs_double[i]);
                break;
        }
        draw_string(x_pixel_prev+37,y_pixel_prev+10,WHITE,print_string,1);
    }
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Starts clock for SPI
    SPIM_Start();
    Clock_Start();
    spi_device_select(SCREEN_SELECT);
    
    // Resets screen
    Reset_Write(1);
    CyDelay(100);
    Reset_Write(0);
    CyDelay(100);
    Reset_Write(1);
    CyDelay(100);
    
    
    //emFile_1_SPI0_Stop();
    // Calls start screen
    StartScreen();
    
    isr_ClearPending();
    
    isr_Start();
    isr_Enable();
    
    isr_SetPriority(0);
    
    //Enabling VDACs and ADCs
    VDAC8_GS_Start();
    VDAC8_DS_Start();
    ADC_SAR_1_Start();
    
    //Sets touch interrupt mode
    I2C_Start();
    I2C_MasterSendStart(0x38, 0); 
    I2C_MasterWriteByte(0xa4); 
    I2C_MasterWriteByte(0x00);   
    I2C_MasterSendStop();
    I2C_Stop();
    
    FS_Init();
    
    int return_code;    //Going to be used for error displays
    
    int i;  //used for for loop iterations
    int j;  //used for for loop iterations
    int k;  //used for for loop iterations
    
    double y_max_mA;                        //The highest plottable Id in mA    
    
    unsigned int Vth;      //VDAC code for the threshold voltage
    unsigned int Vgs_max;  //VDAC code for the the maximum Vgs that produces < 20 mA
    int x_pixel;
    int y_pixel;
    int x_pixel_prev;
    int y_pixel_prev;
    int y_max_calc;
    
    
    int Vgs_step;                                       //The stepping amount to create the Vgs test points
    unsigned char Vgs_test_points[CURVE_NUM_MAX];       //The Vgs stepping points of ammount specified in settings.h
    
    double Vgs_points_double[CURVE_NUM_MAX];            //The actual Vgs output by DAC
    FS_FILE * pFile;
    int debug;
    int SD_files_written = 0;
    int device_selection_prev = -1;
    
    //global variable intializations
    device_selection = -1;
    
    spi_device_select(SD_SELECT);
    
    debug = FS_MountEx("PSOC",FS_MOUNT_RW);
//    if (debug <= 0)
//    {
//        spi_device_select(SCREEN_SELECT);
//        draw_button(320,240,BLACK,WHITE,"NO MOUNT");
//        CyDelay(2000);
//        spi_device_select(SD_SELECT);
//    }
    pFile = FS_FOpen("test.txt", "w");
//    if (pFile == 0)
//    {
//        char no_open[] = "NO OPEN";
//        //spi_device_select(SCREEN_SELECT);
//        draw_button(0,0,320,240,BLACK,WHITE,no_open);
//        CyDelay(2000);
//        //spi_device_select(SD_SELECT);
//    }
    const char text[] = "Can Write";
    FS_Write(pFile,text,strlen(text));
    FS_FClose(pFile);
    spi_device_select(SCREEN_SELECT);
    for(;;)
    { 
        if (device_selection != -1)
        {
            device_selection_prev = device_selection;
        }
        if(device_selection == -1)
        {
            draw_warning_screen();
        }
        else
        {
            draw_options_screen();
        }
        for(;;)
        {
            if(screen_state == 2)
            {
                break;
            } else if (screen_state == DEBUG_SCREEN)
            {
                draw_debug_screen(0,0);
                draw_choose_screen();
            }
        }
        if(write_sd)
        {
            SD_files_written++;
        }
        set_transistor_test_type(device_selection);
        if(device_selection < 2)
        {
            
            Vth = vgs_th_find(VDAC_G_B_MAX,0,VDAC_N_1_VOLT);
        }
        else
        {
            Vth = vgs_th_find(VDAC_G_B_MAX,VDAC_G_1_VOLT,VDAC_P_1_VOLT);
            //vgs_max, vgs_min,Vdac
            
        }
        if (Vth == 0)
        {
            fill_screen(BLACK);
            draw_string(100,150,WHITE,"NO VTH FOUND",1);
            CyDelay(2000);
        }
        if(device_selection < 2)
        {
            Vgs_max = vgs_max_id_find(Vth,vds_high_vdac_code);
        } else
        {
            Vgs_max = vgs_max_id_find(Vth,(VDAC_D_C_P_MAX - vds_high_vdac_code));
        }
        Vgs_step = (Vgs_max - Vth)/(curve_nums-1); //Creating the step size for linearlly spaced
        Vgs_test_points[0] = Vth;
        switch(device_selection)
        {
            case 0:
                Vgs_points_double[0] = Vth*4.096/256.0;
                break;
            case 1:
                Vgs_points_double[0] = (Vth*4.096/256.0 - 0.7)/26.0;
                break;
            case 2:
                Vgs_points_double[0] = -Vth*4.096/256.0;
                break;
            case 3:
                Vgs_points_double[0] = (-15 + (Vth*4.096/256.0))/26.0;
                break;
        }
        //Creating Vgs test point 
        for (i=1; i < curve_nums; i++)
        {
            Vgs_test_points[i] = (Vgs_test_points[i-1] + Vgs_step);
            switch(device_selection)
            {
                case 0:
                    Vgs_points_double[i] = Vgs_test_points[i]*4.096/256.0;
                    break;
                case 1:
                    Vgs_points_double[i] = (Vgs_test_points[i]*4.096/256.0 - 0.7)/26.0;
                    break;
                case 2:
                    Vgs_points_double[i] = Vgs_test_points[i]*4.096/256.0 - P_SOURCE_VOLTAGE;
                    break;
                case 3:
                    Vgs_points_double[i] = (-15 + Vgs_test_points[i]*4.096/256.0)/26.0;
                    break;
            }
        }
       
        y_max_mA = 0.0;
        if(cooldown_time) 
        //calibrates the plotting of the grid
        //if there is no cooldown enabled it will force the
        //scale due to unpredictable curves because of heat
        {
            for (i = 0; i <num_avg;i++)
            {
                y_max_mA += single_test(vds_high_vdac_code,Vgs_test_points[curve_nums-1]);
            }
            y_max_mA /= num_avg;
        } else
        {
            y_max_mA = 29.0;
        }
        y_max_calc = (int) (y_max_mA);
        y_max_calc = (y_max_calc - (y_max_calc % 5) + 5);
        draw_coordinates(y_max_calc,device_selection);
        run_test(y_max_calc,Vgs_test_points,Vgs_points_double,device_selection,SD_files_written);
        
        VDAC8_DS_SetValue(0);
        VDAC8_GS_SetValue(0);
        //fillScreen(WHITE);

        for(;;)
        {
            if(screen_state != PLOT_SCREEN)
            {
                break;
            }
        }     
    }
}