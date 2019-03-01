#include "project.h"
#include "screen.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "settings.h"

#define VDAC_G_B_MAX 255 //Max VDAC code for the Gate/Base 
#define VDAC_D_C_MAX 188 //Max VDAC for the Drain/Common
#define VDS_NMOS_LENGTH ((VDAC_D_C_MAX/VD_STEP_NMOS) + 1)
#define VCE_NPN_LENGTH  ((VDAC_D_C_MAX/VC_STEP_NPN) + 1)
#define VDS_PMOS_LENGTH ((VDAC_D_C_MAX/VD_STEP_PMOS) + 1)
#define VCE_PNP_LENGTH  ((VDAC_D_C_MAX/VC_STEP_PNP) + 1)
#define VDAC_N_1_VOLT 21
#define VDAC_P_1_VOLT 13
#define ADC_GAIN 51.7
#define Y_RES 240
#define X_RES 320

//The lengths of Drain or Common testing points

//Conducts a test for a singular Vds and Vgs
double single_test(unsigned char Vds, unsigned char Vgs)
{
    double Output;
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
    double          Id; 
	//The Drain Current | Id_real = Id/100
    
    VDAC8_DS_SetValue(Vds_max);
	//Sets Vds = 188/256 * 4.096 * 3 = 9V (max Vds to test wtih) to find max current
    for(Vgs = Vth; Vgs < Vgs_max; Vgs++)
    {
        Id = single_test_preset_vds(Vgs);
        if (Id >= ID_MAX)
        {
            break; //Stop stepping once max current is hit
        }
    }
    return Vgs - 1; //Returns the previous Vgs step to avoid going past 20mA
}



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Starts clock for SPI
    SPIM_Start();
    Clock_Start();
    
    // Resets screen
    Reset_Write(1);
    CyDelay(500);
    Reset_Write(0);
    CyDelay(500);
    Reset_Write(1);
    CyDelay(500);
    
    // Calls start screen
    StartScreen();
    
    // Fills screen in black
    fillScreen(BLACK);  
    
    //Enabling VDACs and ADCs
    VDAC8_GS_Start();
    VDAC8_DS_Start();
    ADC_SAR_1_Start();
    
    int return_code;    //Going to be used for error displays
    
    int i;  //used for for loop iterations
    int j;  //used for for loop iterations
    int k;  //used for for loop iterations
    
    unsigned char device_selection = 0;     //The device selected 0: NMOS, 1: PMOS, 3: NPN, 4: PNP
    int y_max_mA = 25;                    //The highest plottable Id in mA
    int x_max_mV = 10000;                  //the highest plottable Vds in mV
    
    int Vth;      //VDAC code for the threshold voltage
    int Vgs_max;  //VDAC code for the the maximum Vgs that produces < 20 mA
    int x_pixel;
    int y_pixel;
    int x_pixel_prev;
    int y_pixel_prev;
    int curve_color[CURVE_NUM] = {BLUE, GREEN, RED, ORANGE};
    
    unsigned char Vgs_step;                         //The stepping amount to create the Vgs test points
    unsigned char Vgs_test_points[CURVE_NUM];       //The Vgs stepping points of ammount specified in settings.h
    unsigned char Vds_test_points[VDS_NMOS_LENGTH]; //The Vds stepping points of ammount specified in settings.h
    
    double Output_data_y[CURVE_NUM][VDS_NMOS_LENGTH] = {0};   //The output data of Id NMOS trace in mA
    double Output_data_x[VDS_NMOS_LENGTH];                   //The Vds points used. Used for plottings
    double Id[AVG];
    double Id_avg;
    
    
    //for(;;)
    //{    
                ADC_SAR_1_Wakeup();
                //case 0:
                //NMOS input
                Vth = vgs_th_find(VDAC_G_B_MAX,VDAC_N_1_VOLT);
                if (Vth < 0)
                {
                    return 0;
                }
                Vgs_max = vgs_max_id_find(Vth,VDAC_D_C_MAX,220);
                Vgs_step = (Vgs_max - Vth)/(CURVE_NUM-1); //Creating the step size for linearlly spaced 
                Vgs_test_points[0] = Vth;
                for (i=1; i < CURVE_NUM; i++)
                {
                    Vgs_test_points[i] = (Vgs_test_points[i-1] + Vgs_step);
                }
                Vds_test_points[0] = 0;
                Output_data_x[0] = 0;
                for(i=1; i < VDS_NMOS_LENGTH; i++)
                {
                    Vds_test_points[i] = Vds_test_points[i-1] + VD_STEP_NMOS;
                    Output_data_x[i] = Vds_test_points[i-1] * 3.0 * 4096.0 / 256.0;
                }
                for(i = 0; i < CURVE_NUM; i++)
                {
                    for(j = 0; j <VDS_NMOS_LENGTH; j++)
                    {
                        for(k=0; k < AVG; k++)
                        {
                            Id[k] = single_test(Vds_test_points[j],Vgs_test_points[i]);
                            if (k == 0)
                            {
                                Id_avg = Id[k];
                            }
                            else
                            {
                                Id_avg = Id[k] + Id_avg;
                            }
                        }
                        Id_avg = Id_avg/AVG;
                        if (j==0)
                        {
                            y_pixel_prev = (int) (Id_avg*y_max_mA/Y_RES);
                            x_pixel_prev = (int) (Output_data_x[j]*x_max_mV)/X_RES;
                        }
                        else
                        {
                            y_pixel = (int) ((Id_avg*Y_RES)/y_max_mA);
                            x_pixel = (int) ((Output_data_x[j]*X_RES)/x_max_mV);
                            draw_line(x_pixel_prev,y_pixel_prev,x_pixel,y_pixel,curve_color[i]);
                            y_pixel_prev = y_pixel;
                            x_pixel_prev = x_pixel;
                        }
                    }
                }
////            case 1:
////                //NPN input
////                Vth =  126; //vgs_th_find(VDAC_G_B_MAX,VDAC_N_1_VOLT);
////                if (Vth < 0)
////                {
////                    //Print error function
////                }
////                Vgs_max = 188;  //vgs_max_id_find(Vth,VDAC_D_C_MAX,VDAC_G_B_MAX);
////                Vgs_step = (Vgs_max - Vth)/CURVE_NUM; //Creating the step size for linearlly spaced 
////                Vgs_test_points[0] = Vth;
////                for (i=1; i < CURVE_NUM; i++)
////                {
////                    Vgs_test_points[i] = (Vgs_test_points[i-1] + Vgs_step);
////                }
////                Vds_test_points[0] = 0;
////                Output_data_x[0] = 0;
////                for(i=1; i < VDS_NMOS_LENGTH; i++)
////                {
////                    Vds_test_points[i] = Vds_test_points[i-1] + VD_STEP_NMOS;
////                    Output_data_x[i] = Vds_test_points[i-1]/2560.0 * 3.0 * 4.096; //Translates VDAC code to Ib in mA
////                }
////                for(i = 0; i < CURVE_NUM; i++)
////                {
////                    for(j = 0; j < VDS_NMOS_LENGTH; j++)
////                    {
////                        Output_data_y[i][j] = single_test(Vds_test_points[j],Vgs_test_points[i]);
////                    }
////                }
////            case 2:
////                //PMOS input
////                Vth =  126; //vgs_th_find(VDAC_G_B_MAX,VDAC_P_1_VOLT);
////                if (Vth < 0)
////                {
////                    //Print error function
////                }
////                Vgs_max = 188;  //vgs_max_id_find(Vth,VDAC_D_C_MAX,VDAC_G_B_MAX);
////                Vgs_step = (Vgs_max - Vth)/CURVE_NUM; //Creating the step size for linearlly spaced 
////                Vgs_test_points[0] = Vth;
////                for (i=1; i < CURVE_NUM; i++)
////                {
////                    Vgs_test_points[i] = (Vgs_test_points[i-1] + Vgs_step);
////                }
////                Vds_test_points[0] = 0;
////                Output_data_x[0] = 0;
////                for(i=1; i < VDS_NMOS_LENGTH; i++)
////                {
////                    Vds_test_points[i] = Vds_test_points[i-1] + VD_STEP_NMOS;
////                    Output_data_x[i] = Vds_test_points[i-1]/2560.0 * 3.0 * 4.096; //Translates VDAC code to Ib in mA
////                }
////                for(i = 0; i < CURVE_NUM; i++)
////                {
////                    for(j = 0; j < VDS_NMOS_LENGTH; j++)
////                    {
////                        Output_data_y[i][j] = single_test(Vds_test_points[j],Vgs_test_points[i]);
////                    }
////                }
////            case 3:
////                //PNP input
////                Vth =  126; //vgs_th_find(VDAC_G_B_MAX,VDAC_P_1_VOLT);
////                if (Vth < 0)
////                {
////                    //Print error function
////                }
////                Vgs_max = 188;  //vgs_max_id_find(Vth,VDAC_D_C_MAX,VDAC_G_B_MAX);
////                Vgs_step = (Vgs_max - Vth)/CURVE_NUM; //Creating the step size for linearlly spaced 
////                Vgs_test_points[0] = Vth;
////                for (i=1; i < CURVE_NUM; i++)
////                {
////                    Vgs_test_points[i] = (Vgs_test_points[i-1] + Vgs_step);
////                }
////                Vds_test_points[0] = 0;
////                Output_data_x[0] = 0;
////                for(i=1; i < VDS_NMOS_LENGTH; i++)
////                {
////                    Vds_test_points[i] = Vds_test_points[i-1] + VD_STEP_NMOS;
////                    Output_data_x[i] = Vds_test_points[i-1]/2560.0 * 3.0 * 4.096; //Translates VDAC code to Ib in mA
////                }
////                for(i = 0; i < CURVE_NUM; i++)
////                {
////                    for(j = 0; j < VDS_NMOS_LENGTH; j++)
////                    {
////                        Output_data_y[i][j] = single_test(Vds_test_points[j],Vgs_test_points[i]);
////                    }
////                }
        
        ADC_SAR_1_Sleep();
    //}
        VDAC8_DS_SetValue(0);
        VDAC8_GS_SetValue(0);
//        //fillScreen(WHITE);
//
//    //}
}