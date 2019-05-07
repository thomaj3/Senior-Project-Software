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
#define VDAC_D_C_MAX    188 //Max VDAC for the Drain/Common
#define VDS_NMOS_LENGTH ((VDAC_D_C_MAX/VD_STEP_NMOS) + 1)
#define VCE_NPN_LENGTH  ((VDAC_D_C_MAX/VC_STEP_NPN) + 1)
#define VDS_PMOS_LENGTH ((VDAC_D_C_MAX/VD_STEP_PMOS) + 1)
#define VCE_PNP_LENGTH  ((VDAC_D_C_MAX/VC_STEP_PNP) + 1)
#define VDAC_N_1_VOLT   21
#define VDAC_P_1_VOLT   13
#define ADC_GAIN        52.0


//The lengths of Drain or Common testing points

void set_transistor_test_type(void)
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
    
    double Output;
    
    ADC_SAR_1_Wakeup();                                                     //wakeup from ADC reset
    VDAC8_DS_SetValue(Vds);                                                 //Set Vg
    VDAC8_GS_SetValue(Vgs);                                                 //Set Vd
    CyDelay(SETTLING_WAIT_TIME);                                            //wait for circuit to settle
    ADC_SAR_1_StartConvert();                                               //Trigger ADC conversion
    ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);                   //wait until the end of conversion
    ADC_SAR_1_StopConvert();                                                //stop conversion
    Output = (ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16())/ADC_GAIN); //ID calculation from Id code
    ADC_SAR_1_Sleep();                                                      //set ADC to sleep for reset
    if(cooldown_time)
    {
        //if cooldown is enabled VDACs will turn off and let DUT cool for cooldown_time * duty_cycle
        VDAC8_DS_SetValue(0);
        VDAC8_GS_SetValue(0);
        CyDelay(cooldown_time*SETTLING_WAIT_TIME);
    }
    return Output;
}

double single_test_preset_vds(unsigned char Vgs)
{
    double Output;
    
    ADC_SAR_1_Wakeup();                                                     //wakeup from ADC reset
    VDAC8_GS_SetValue(Vgs);                                                 //Set Vd
    CyDelay(SETTLING_WAIT_TIME);                                            //wait for circuit to settle
    ADC_SAR_1_StartConvert();                                               //Trigger ADC conversion
    ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);                   //wait until the end of conversion
    ADC_SAR_1_StopConvert();                                                //stop conversion
    Output = (ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16())/ADC_GAIN); //ID calculation from Id code
    ADC_SAR_1_Sleep();                                                      //set ADC to sleep for reset
    return Output;
}
    

//Finds Vth (The minimum Vgs needed to turn the transistor by sorting through Vgs's until 
//a minumum current of 1 mA is found Id is found by a 1 Ohm series resistor whose potential 
//difference is magnitifed 100 fold for accurate reading
int vgs_th_find(unsigned char Vgs_max, unsigned char Vds)
{
    unsigned char   Vgs;           
	//The Gate-Drain Voltage difference | Vds_real = Vds/256 * 4.096 * 3 (OpAmp gain)
    double          Id=0;         
	//The Drain Current | Id_real = Id/100
    int i;
    VDAC8_DS_SetValue(Vds); //Set Vds to 1 Volt
    VDAC8_GS_SetValue(0);
    for(Vgs = 0; Vgs < Vgs_max; Vgs++)
    {
        Id = single_test_preset_vds(Vgs);
        
        if(Id > ID_TH)
        {
            //Once Id > 1 mV transistor is "on" and we can return Vgs as Vth
            return Vgs;
        }
    }
    return 0; //If a Vth cannot be found
}

//Finds the MAX current 20mA, Id is found through a 100 Ohm series resistor
//Sweeps through Vgs until a max current of 20 mA is found
//Therefor ID_MAX = 20*100 == 2000
unsigned int vgs_max_id_find(unsigned char Vth, unsigned char Vds_max, unsigned char Vgs_max)
{
    unsigned char   Vgs;
	//The Gate-Source Voltage difference | Vgs_real = Vgs/256 * 4.096
    double          Id=0.0; 
	//The Drain Current | Id_real = Id/100
    VDAC8_DS_SetValue(Vds_max);
	//Sets Vds = 188/256 * 4.096 * 3 = 9V (max Vds to test wtih) to find max current
    int i;
    for(Vgs = Vth; Vgs < Vgs_max; Vgs++)
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
int run_test(int y_max, unsigned char Vgs_test_points[curve_nums],double Vgs_double[curve_nums], int SD_files_written)
{
    int i,j,k;                              //loop iterations
    double Id_avg;                          //exact Id_value averaged
    char print_string[20];                  //dummy string to be used
    char file_name[11]="data";              //beginning of file name to be appended
    char SD_files_written_str[3];
    int y_pixel_prev, x_pixel_prev;         //the previous pixel calculation to be used for line drawing
    int y_pixel, x_pixel;                   //the current pixel calcuation to be used for line drawing
    int curve_color[CURVE_NUM_MAX] = {BLUE, GREEN, RED, ORANGE, CYAN, PINK};
    
    sprintf(SD_files_written_str,"%d",SD_files_written);
    strcat(file_name,SD_files_written_str);
    strcat(file_name,".txt");
    //create SD file name
    for(i = 0; i < curve_nums; i++)
    {
        if(write_sd==1)
        {
            
            write_header_info(file_name,i,Vgs_double);
        }
        //ADC_SAR_1_Wakeup();//wakeup from sleep for reset purposes
        for(j = 0; j < vds_high_vdac_code; j++)
        {
            if(/*!screen_state*/ screen_state != PLOT_SCREEN)
            {
                //break from test in case of exit
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
                    Id_avg += single_test(VDAC_D_C_MAX - j, Vgs_double[i]);
                }
            }
            Id_avg /= num_avg;
            if(write_sd==1)
            {
                write_data(file_name,Id_avg,j);//update CSV File with new Id/Ic
            }
            //creating pixel coordinates via ratios (Id/Id_max == y_pixel/y_resolution)
            y_pixel = (int) ((Id_avg*Y_RES*0.8)/(y_max));
            x_pixel = (int) (VDAC_D_C_MAX * j)/vds_high_vdac_code;
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
        //labeling of Vgs or Ib at the end of the curve
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
    
    int i;                                              //used for for loop iterations
    
    double y_max_mA;                                    //The highest plottable Id in mA    
    
    unsigned int Vth;                                   //VDAC code for the threshold voltage
    unsigned int Vgs_max;                               //VDAC code for the the maximum Vgs that produces < 20 mA
    int y_max_calc;
    
    
    unsigned char Vgs_step;                             //The stepping amount to create the Vgs test points
    unsigned char Vgs_test_points[CURVE_NUM_MAX];       //The Vgs stepping points of ammount specified in settings.h
    
    double Vgs_points_double[CURVE_NUM_MAX];            //The actual Vgs output by DAC
    FS_FILE * pFile;
    int debug;
    int SD_files_written = 0;                           //The amount of SD files written, used to name SD files
    int device_selection_prev = -1;                     //Used in keeping track of how many screens
    
    //global variable intializations
    device_selection = -1;                              //initalizing device_selection for infinite while loops
    
    spi_device_select(SD_SELECT);
    
    //SD DEBUG START
    
    debug = FS_MountEx("PSOC",FS_MOUNT_RW);
//    if (debug <= 0)
//    {
//        spi_device_select(SCREEN_SELECT);
//        draw_button(320,240,BLACK,WHITE,"NO MOUNT");
//        CyDelay(2000);
//        spi_device_select(SD_SELECT);
//    }
    pFile = FS_FOpen("test.txt", "w+");
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
    const char text2[] = "CAN WRITE";
    pFile = FS_FOpen("text.txt","w+");
    FS_Write(pFile,text2,strlen(text2));
    FS_FClose(pFile);
    
    spi_device_select(SCREEN_SELECT);
    //SD DEBUG END
    for(;;)
    { 
        if (device_selection != -1)
        {
            device_selection_prev = device_selection; //remember the previous screen
        }
        if(device_selection == -1) //draw the data loss screen and wait for touch input
        {
            draw_warning_screen();
        }
        else
        {
            draw_options_screen();
        }
        for(;;)
        {
            if(screen_state == 2) //wait until device and options have been selected
            {
                break; 
            } else if (screen_state == DEBUG_SCREEN) //PIZZA TIME
            {
                draw_debug_screen(0,0);
                draw_choose_screen();
            }
        }
        if(write_sd)
        {
            SD_files_written++; 
            //if SD writing is enabled increment the SD_files_written for file naming
        }
        set_transistor_test_type();//MUX selection for either N or P type test
        if(device_selection < 2)
        {
            
            Vth = vgs_th_find(VDAC_G_B_MAX,VDAC_N_1_VOLT); //find Vt under |Vds| = 1 V
        }
        else
        {
            Vth = vgs_th_find(VDAC_G_B_MAX,VDAC_P_1_VOLT); // find Vt under |Vds| =  1V
        }
        if (Vth == 0)
        {
            draw_button(0,0,320,240,BLACK,WHITE,"NO VT FOUND CHECK POWER SUPPLIES");
            CyDelay(1000);
            //display warning screen for no Vt found
        }
            
        Vgs_max = vgs_max_id_find(Vth,VDAC_D_C_MAX,220);    //find the max Vgs with current draw <= 20 mA
        Vgs_step = (Vgs_max - Vth)/(curve_nums-1);          //Create step for linearly sapce [Vt,Vgs_max]
        Vgs_test_points[0] = Vth;
        switch(device_selection)
        {
            //creating equivalent double format Vgs or Ib for labeling 
            case 0:
                Vgs_points_double[0] = Vth*4.096/256.0;
                //Vgs_out = Vdac_code*4.096/256;
                break;
            case 1:
                Vgs_points_double[0] = (Vth*4.096/256.0 - 0.7)/26.0;
                break;
            case 2:
                Vgs_points_double[0] = -12 + Vth*4.096/256.0;
                break;
            case 3:
                Vgs_points_double[0] = (-12 + (Vth*4.096/256.0))/26.0;
                break;
        }
        //Creating Vgs test point 
        for (i=1; i < curve_nums; i++)
        {
            Vgs_test_points[i] = (Vgs_test_points[i-1] + Vgs_step);
            //creating VDAC test points from stepping increment
            switch(device_selection)
            {
                //creating equivalent double format Vgs or Ib for labeling
                case 0:
                    Vgs_points_double[i] = Vgs_test_points[i]*4.096/256.0;
                    break;
                case 1:
                    Vgs_points_double[i] = (Vgs_test_points[i]*4.096/256.0 - 0.7)/26.0;
                    break;
                case 2:
                    Vgs_points_double[i] = -15 + Vgs_test_points[i]*4.096/256.0;
                    break;
                case 3:
                    Vgs_points_double[i] = (-15 + Vgs_test_points[i]*4.096/256.0)/26.0;

                    break;
            }
        }
       
        y_max_mA = 0.0;
        //calibrates the plotting of the grid
        //if there is no cooldown enabled it will force the
        //scale due to unpredictable curves because of heat
        if(cooldown_time) 
        {
            for (i = 0; i <num_avg;i++)
            {
                y_max_mA += single_test(VDAC_D_C_MAX,Vgs_test_points[curve_nums-1]);
            }
            y_max_mA /= num_avg;
        } else
        {
            y_max_mA = 29.0;
        }
        y_max_calc = (int) (y_max_mA);
        y_max_calc = (y_max_calc - (y_max_calc % 5) + 5);
        //creates a y_max used for calcuation that rounds up to nearest multiple of 5
        draw_coordinates(y_max_calc);
        //draw the coordinates based on the y_max_calc
        run_test(y_max_calc,Vgs_test_points,Vgs_points_double,SD_files_written);
        //run curve tracer test
        
        VDAC8_DS_SetValue(0);
        VDAC8_GS_SetValue(0);
        //turn off VDACs

        for(;;)
        {
            if(screen_state != PLOT_SCREEN)
            {
                break;
            }
        }     
    }
}