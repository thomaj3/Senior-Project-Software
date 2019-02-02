#include "project.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "settings.h"
#include "minor_functions.h"
#define VDAC_GS_NMOS_MAX 255
#define VDAC_DS_NMOS_MAX 188
#define VDS_NMOS_LENGTH ((VDAC_DS_NMOS_MAX/VD_STEP_NMOS) + 1)

//Finds Vth (The minimum Vgs needed to turn the transistor by sorting through Vgs's until 
//a minumum current of 1 mA is found Id is found by a 1 Ohm series resistor whose potential 
//difference is magnitifed 100 fold for accurate reading
unsigned short vgs_th_find(unsigned char Vgs_max)
{
    unsigned char   Vgs;        
	//The Gate-Source Voltage difference | Vgs_real = Vgs/256 * 4.096
    unsigned char   Vds = 21;   
	//The Gate-Drain Voltage difference | Vds_real = Vds/256 * 4.096 * 3 (OpAmp gain)
    double          Id;         
	//The Drain Current | Id_real = Id/100
    
    VDAC8_DS_SetValue(Vds); //Set Vds to 1 Volt
    
    for(Vgs = 0; Vgs < Vgs_max; Vgs++)
    {
        VDAC8_GS_SetValue(Vgs);     
		//Step Vgs
        ADC_SAR_1_StartConvert();   
		//Start ADC Conversion
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT); 
		//Wait until end of converstion
        ADC_SAR_1_StopConvert();    
		//Stop Conversion
        Id = ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16()); 
		//Returns mV of the OpAmp output (100x real Id)
        if(Id > ID_TH)
        {
            //Once Id > 1 mV transistor is "on" and we can return Vgs as Vth
            return Vgs;
        }
    }
    return Vgs; //If a Vth cannot be found
}

//Finds the MAX current 20mA, Id is found through a 100 Ohm series resistor
//Sweeps through Vgs until a max current of 20 mA is found
//Therefor ID_MAX = 20*100 == 2000
unsigned short vgs_max_id_find(unsigned char Vth, unsigned char Vds_max, unsigned char Vgs_max)
{
    unsigned char   Vgs;
	//The Gate-Source Voltage difference | Vgs_real = Vgs/256 * 4.096
    double          Id; 
	//The Drain Current | Id_real = Id/100
    
    VDAC8_DS_SetValue(Vds_max);
	//Sets Vds = 188/256 * 4.096 * 3 = 9V (max Vds to test wtih) to find max current
    for(Vgs = Vth; Vgs < Vgs_max; Vgs++)
    {
        //Run through Vgs values until we hit max current of 20mA with max Vds
        VDAC8_GS_SetValue(Vgs); //Step Vgs
        ADC_SAR_1_StartConvert(); //Start ADC Conversion
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT); //Wait until Conversion is Complete
        ADC_SAR_1_StopConvert(); //End conversion
        Id = ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16());
		//Returns the mV of the OpAmp output (100x real Id)
        if (Id >= ID_MAX)
        {
            break; //Stop stepping once max current is hit
        }
    }
    return Vgs - 1; //Returns the previous Vgs step to avoid going past 20mA
}


double single_test(unsigned char Vds, unsigned char Vgs)
{
    double Output;
    VDAC8_DS_SetValue(Vds);
    VDAC8_GS_SetValue(Vgs);
    CyDelay(10);
    ADC_SAR_1_StartConvert();
    ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
	//waiting until conversion is over
    ADC_SAR_1_StopConvert();
    Output = ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16()/100);
    return Output;
}

int main(void)
{
    //Enabling VDACs and ADCs
    VDAC8_GS_Start();
    VDAC8_DS_Start();
    ADC_SAR_1_Start();
    
    int return_code;    //Going to be used for error displays
    
    int i;  //used for for loop iterations
    int j;  //used for for loop iterations
    
    short Vth;      //VDAC code for the threshold voltage
    short Vgs_max;  //VDAC code for the the maximum Vgs that produces < 20 mA 
    
    unsigned char Vgs_step;                         //The stepping amount to create the Vgs test points
    unsigned char Vgs_test_points[CURVE_NUM];       //The Vgs stepping points of ammount specified in settings.h
    unsigned char Vds_test_points[VDS_NMOS_LENGTH]; //The Vds stepping points of ammount specified in settings.h
    
    double Output_data_nmos_id[CURVE_NUM][VDS_NMOS_LENGTH] = {0};   //The output data of Id NMOS trace in mA
    double Output_data_nmos_vds[VDS_NMOS_LENGTH];                   //The Vds points used. Used for plotting
    
    
    for(;;)
    {
        //Assume NMOS input
        Vth =  126; //vgs_th_find();
        if (Vth < 0)
        {
            //Print error function
        }
        Vgs_max = 188;  //vgs_max_id_find(Vth);
        Vgs_step = (Vgs_max - Vth)/CURVE_NUM; //Creating the step size for linearlly spaced 
        Vgs_test_points[0] = Vth;
        for (i=1; i < CURVE_NUM; i++)
        {
            Vgs_test_points[i] = Vgs_test_points[i-1] + Vgs_step;
        }
        Vds_test_points[0] = 0;
        Output_data_nmos_vds[0] = 0;
        for(i=1; i < VDS_NMOS_LENGTH; i++)
        {
            Vds_test_points[i] = Vds_test_points[i-1] + VD_STEP_NMOS;
            Output_data_nmos_vds[i] = Vds_test_points[i-1]/256.0 * 3.0 * 4.096;
        }
        for(i = 0; i < CURVE_NUM; i++)
        {
            for(j = 0; j < VDS_NMOS_LENGTH; j++)
            {
                Output_data_nmos_id[i][j] = single_test(Vds_test_points[j],Vgs_test_points[i]);
            }
        }
    }
}
/* [] END OF FILE */
