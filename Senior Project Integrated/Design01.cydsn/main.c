#include "project.h"
#include "screen.h"
#include "font.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "settings.h"
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
#define CURVE_MAX       10


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
    return Output;
}

double single_test_preset_vds(unsigned char Vgs)
{
    double Output;
    
    VDAC8_GS_SetValue(Vgs);
    CyDelay(SETTLING_WAIT_TIME);
    ADC_SAR_1_StartConvert();
    ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
	//waiting until conversion is over
    ADC_SAR_1_StopConvert();
    Output = (ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16())/ADC_GAIN);
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
    ADC_SAR_1_Wakeup();
    VDAC8_DS_SetValue(Vds); //Set Vds to 1 Volt
    VDAC8_GS_SetValue(0);
    for(Vgs = 0; Vgs < Vgs_max; Vgs++)
    {
        Id = single_test_preset_vds(Vgs);
        if(Id > ID_TH)
        {
            //Once Id > 1 mV transistor is "on" and we can return Vgs as Vth
            ADC_SAR_1_Sleep();
            return Vgs;
        }
    }
    ADC_SAR_1_Sleep();
    return 0; //If a Vth cannot be found
}

//Finds the MAX current 20mA, Id is found through a 100 Ohm series resistor
//Sweeps through Vgs until a max current of 20 mA is found
//Therefor ID_MAX = 20*100 == 2000
unsigned int vgs_max_id_find(unsigned char Vth, unsigned char Vds_max, unsigned char Vgs_max)
{
    unsigned char   Vgs;
	//The Gate-Source Voltage difference | Vgs_real = Vgs/256 * 4.096
    double          Id; 
	//The Drain Current | Id_real = Id/100
    ADC_SAR_1_Wakeup();
    VDAC8_DS_SetValue(Vds_max);
	//Sets Vds = 188/256 * 4.096 * 3 = 9V (max Vds to test wtih) to find max current
    for(Vgs = Vth; Vgs < Vgs_max; Vgs++)
    {
        Id = single_test_preset_vds(Vgs);
        if (Id >= ID_MAX)
        {
            ADC_SAR_1_Sleep();
            VDAC8_DS_SetValue(0);
            VDAC8_GS_SetValue(0);
            return Vgs-1; //Stop stepping once max current is hit
        }
    }
    ADC_SAR_1_Sleep();
    VDAC8_DS_SetValue(0);
    VDAC8_GS_SetValue(0);
    return Vgs; //Returns the previous Vgs step to avoid going past 20mA
}

//This function runs the main test, it intakes the y_max used to calculate the
//pixels for line segments and the Vgs test points
int run_test(int y_max, unsigned char Vgs_test_points[CURVE_NUM],double Vgs_double[CURVE_NUM], unsigned char device_selection)
{
    int i,j,k;
    double Id;
    double Id_avg;
    char print_string[20];
    int y_pixel_prev, x_pixel_prev;
    int y_pixel, x_pixel;
    int curve_color[CURVE_MAX] = {BLUE, GREEN, RED, ORANGE, CYAN, PINK, LIGHTGREY, OLIVE, WHITE, GREENYELLOW};
    
    for(i = 0; i < CURVE_NUM; i++)
    {
        write_header_info("data.txt",device_selection,i,Vgs_double); 
        ADC_SAR_1_Wakeup();//wakeup from sleep for reset purposes
        for(j = 0; j <VDAC_D_C_MAX; j++)
        {
            if(!screen_state)
            {
                return 0;   
            }
            Id_avg = 0.0;//reset Id Value
            //Averaging multiple tests to elminate noise
            for(k=0; k<AVG; k++)
            {
                if(device_selection < 2) //if testing N-Type Devices
                {
                    Id = single_test(j,Vgs_test_points[i]);
                }
                else //if testing P-Type devices
                {
                    Id = single_test(VDAC_D_C_MAX - j, Vgs_double[i]);
                }
                Id_avg += Id;
            }
            Id_avg /= AVG;
            write_data("data.txt",Id_avg,j,device_selection);//update CSV File with new Id/Ic
            //creating pixel coordinates via rations (Id/Id_max == y_pixel/y_resolution)
            y_pixel = (int) ((Id_avg*Y_RES)/(1.25*y_max));
            x_pixel = (int) j;
            if (j > 0) //only draw a line if 2 points have been tested already
            {
                draw_line(x_pixel_prev+30,y_pixel_prev+10,x_pixel+30,y_pixel+10,curve_color[i]);
            }
            y_pixel_prev = y_pixel;
            x_pixel_prev = x_pixel;
            }
        ADC_SAR_1_Sleep(); //sleep to reset ADC between curves
        switch(device_selection)
        {
            case 0:
                sprintf(print_string,"%5.3f V",Vgs_double[i]);
                break;
            case 1:
                sprintf(print_string,"%.3f MIL A",Vgs_double[i]);
                break;
            case 2:
                sprintf(print_string,"%6.3f V",Vgs_double[i]);
                break;
            case 3:
                sprintf(print_string,"%6.3f MIL A",Vgs_double[i]);
                break;
        }
        draw_string(x_pixel_prev+35,y_pixel_prev+10,WHITE,print_string,1);
    }
    
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Starts clock for SPI
    SPIM_Start();
    Clock_Start();
    
    
    // Resets screen
    Reset_Write(1);
    CyDelay(100);
    Reset_Write(0);
    CyDelay(100);
    Reset_Write(1);
    CyDelay(100);
    
    
    
    // Calls start screen
    StartScreen();
    
    // Fills screen in black    
      
    
    isr_ClearPending();
    
    isr_Start();
    isr_Enable();
    
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
    
    CURVE_NUM1 = 4;
    
    int return_code;    //Going to be used for error displays
    
    int i;  //used for for loop iterations
    int j;  //used for for loop iterations
    int k;  //used for for loop iterations
    
    double y_max_mA;                        //The highest plottable Id in mA    
    double x_max_mV = 10000;                   //the highest plottable Vds in mV
    
    unsigned int Vth;      //VDAC code for the threshold voltage
    unsigned int Vgs_max;  //VDAC code for the the maximum Vgs that produces < 20 mA
    int x_pixel;
    int y_pixel;
    int x_pixel_prev;
    int y_pixel_prev;
    int y_max_calc;
    
    
    unsigned char Vgs_step;                         //The stepping amount to create the Vgs test points
    unsigned char Vgs_test_points[CURVE_NUM];       //The Vgs stepping points of ammount specified in settings.h
    
    double Output_data_y[CURVE_NUM][VDS_NMOS_LENGTH] = {0};     //The output data of Id NMOS trace in mA
    double Output_data_x[VDS_NMOS_LENGTH];                      //The Vds points used. Used for plottings
    double Vgs_points_double[CURVE_NUM];                        //The actual Vgs output by DAC
    FS_FILE * pFile;
    int debug;
    
    FS_Init();
    debug = FS_MountEx("PSOC",FS_MOUNT_RW);
//    if (debug <= 0)
//    {
//        draw_string(100,80,WHITE,"NO MOUNT");
//    }
    pFile = FS_FOpen("test.txt", "+w");
//    if (pFile == 0)
//    {
//        draw_string(100,100,WHITE,"NO OPEN");
//    }
    const char text[] = "Can Write";
    FS_Write(pFile,text,strlen(text));
    FS_FClose(pFile);
    
    for(;;)
    { 
        draw_choose_screen();
        device_selection = -1;
        while(device_selection < 0)
        {
            
        }
        while(screen_state != 2)
        {
            
        }
        set_transistor_test_type(device_selection);
        if(device_selection < 2)
        {
            
            Vth = vgs_th_find(VDAC_G_B_MAX,VDAC_N_1_VOLT);
        }
        else
        {
            Vth = vgs_th_find(VDAC_G_B_MAX,VDAC_P_1_VOLT);
        }
        if (Vth == 0)
        {
            fill_screen(BLACK);
            draw_string(120, 160, WHITE, "VTH CANNOT BE FOUND",1);
            create_file_with_text("log.txt", "No Threshold Voltage found, check power supplies");
//            return 0;
        }
        Vgs_max = vgs_max_id_find(Vth,VDAC_D_C_MAX,220);
        Vgs_step = (Vgs_max - Vth)/(CURVE_NUM-1); //Creating the step size for linearlly spaced
        Vgs_test_points[0] = Vth;
        switch(device_selection)
        {
            case 0:
                Vgs_points_double[0] = Vth*4.096/256.0;
                break;
            case 1:
                Vgs_points_double[0] = (Vth*4.096/256.0 - 0.7)/10;
                break;
            case 2:
                Vgs_points_double[0] = -15 + Vth*4.096/256.0;
                break;
            case 3:
                Vgs_points_double[0] = (-15 + (Vth*4.096/256.0))/10;
                break;
        }
        //Creating Vgs test point 
        for (i=1; i < CURVE_NUM; i++)
        {
            Vgs_test_points[i] = (Vgs_test_points[i-1] + Vgs_step);
            switch(device_selection)
            {
                case 0:
                    Vgs_points_double[i] = Vgs_test_points[i]*4.096/256.0;
                    break;
                case 1:
                    Vgs_points_double[i] = (Vgs_test_points[i]*4.096/256.0 - 0.7)/10;
                    break;
                case 2:
                    Vgs_points_double[i] = -15 + Vgs_test_points[i]*4.096/256.0;
                    break;
                case 3:
                    Vgs_points_double[i] = (-15 + Vgs_test_points[i]*4.096/256.0)/10;
                    break;
            }
        }
        for(i=0; i < VDS_NMOS_LENGTH; i++)
        {
            if(device_selection < 2)
            {
                Output_data_x[i] = i * 4.096 * 3 / 256.0; //actual Vds
            }
            else
            {
                Output_data_x[i] = i * 4.096 * 5 / 256.0;
            }
        }
        ADC_SAR_1_Wakeup();
        y_max_mA = 0.0;
        for (i = 0; i <AVG;i++)
        {
            y_max_mA += single_test(VDAC_D_C_MAX,Vgs_test_points[CURVE_NUM-1]);
        }
        y_max_mA /= AVG;
        y_max_calc = (int) (y_max_mA);
        y_max_calc = (y_max_calc - (y_max_calc % 5) + 5);
        ADC_SAR_1_Sleep(); //Reset SAR from previous tests
        draw_coordinates(y_max_calc,device_selection);
        run_test(y_max_calc,Vgs_test_points,Vgs_points_double,device_selection);
        
        
        ADC_SAR_1_Sleep();
        VDAC8_DS_SetValue(0);
        VDAC8_GS_SetValue(0);
        //fillScreen(WHITE);

        while(screen_state != 0)
        {
            if(screen_state == 0)
            {
                break;
            }
        }
    }
}