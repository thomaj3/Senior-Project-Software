#include "project.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "settings.h"
#include "minor_functions.h"
#define VDAC_GS_MAX 255
#define VDAC_DS_MAX 188

//Finds Vth (The minimum Vgs needed to turn the transistor by sorting through Vgs's until 
//a minumum current of 1 mA is found Id is found by a 1 Ohm series resistor whose potential 
//difference is magnitifed 100 fold for accurate reading
unsigned short vgs_th_find()
{
    unsigned char   Vgs;        
	//The Gate-Source Voltage difference | Vgs_real = Vgs/256 * 4.096
    unsigned char   Vds = 21;   
	//The Gate-Drain Voltage difference | Vds_real = Vds/256 * 4.096 * 3 (OpAmp gain)
    double          Id;         
	//The Drain Current | Id_real = Id/100
    
    VDAC8_DS_SetValue(Vds); //Set Vds to 1 Volt
    /*
    for(Vgs = 0; Vgs < VDAC_GS_MAX; Vgs++)
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
    */
    return 64; //If a Vth cannot be found
}

//Finds the MAX current 20mA, Id is found through a 100 Ohm series resistor
//Sweeps through Vgs until a max current of 20 mA is found
//Therefor ID_MAX = 20*100 == 2000
unsigned short vgs_max_id_find(unsigned char Vth)
{
    unsigned char   Vgs;
	//The Gate-Source Voltage difference | Vgs_real = Vgs/256 * 4.096
    double          Id; 
	//The Drain Current | Id_real = Id/100
    
    VDAC8_DS_SetValue(VDAC_DS_MAX);
	//Sets Vds = 188/256 * 4.096 * 3 = 9V (max Vds to test wtih) to find max current
    for(Vgs = Vth; Vgs < VDAC_GS_MAX; Vgs++)
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
    //return Vgs - 1; //Returns the previous Vgs step to avoid going past 20mA
    return VDAC_GS_MAX;
}


int nmos_sweep_slow()
{
    //returning an error code
    unsigned char   i=0;            
    unsigned char   j=1;
    unsigned char   k;
    unsigned char   Vds;                    
	//The Gate-Drain Voltage difference | Vds_real = Vds/256 * 4.096 * 3 (OpAmp gain)
    unsigned short  Vgs_th;                 
	//The Threshold Voltage, the reguired Vgs to turn on
    unsigned char   Vgs_max;                
	//The Vgs that prompts the largest allowable current
    double          Output_data_nmos_slow_mat[2][CURVE_NUM][VDAC_DS_MAX/VD_STEP_NMOS + 1] = {0};
	//Array for storage of data for output
    unsigned char   Vgs_test_points[6]={0};
	//The 6 Vgs DAC codes for testing
    double          Vgs_step;               
	//The step between Vgs points required for their generation
    Vgs_th = vgs_th_find();                 
	//Find Vth for this transistor
    if(Vgs_th > 255)            
    {
        //If Vgs returns it's "error code" return an error code, 1
        return 1;
    }
    
    Vgs_max = vgs_max_id_find(Vgs_th); //Vgs max is the Vgs that pulls 20 mA
    
    //Doing a linspace between Vth and Vgs_max (the Vgs that pulls 20 mA) for testing points
    
    Vgs_step = (Vgs_max - Vgs_th)/6.0;
    for (k = 0; k < 6; k++)
    {
        if(Vgs_th + k*Vgs_step > VDAC_GS_MAX)
        {
            break; //Esnure we don't go over 4 V
        }
        Vgs_test_points[k] = eight_bit_unsigned_round(Vgs_th + k*Vgs_step);    
    }
    
    //Testing test points
    for(k=0; k < 6; k++)
    {
        if ((k > 0) && (Vgs_test_points[k] == Vgs_test_points[k-1]))
        {
            //Skips a value if it's the same as the previous
            continue;
        }
        VDAC8_GS_SetValue(Vgs_test_points[k]);//Step Vgs
        for(Vds = 0;Vds <= VDAC_DS_MAX; Vds += VD_STEP_NMOS)
        {
            VDAC8_DS_SetValue(Vds);//Step Vds
            
            Output_data_nmos_slow_mat[0][i][0] = ((Vgs_test_points[k])/255.0*4.096);
			//Storing Vgs as first element of array
            Output_data_nmos_slow_mat[1][i][0] = Output_data_nmos_slow_mat[0][i][0];
			//Storing Vgs as first element of array
            
            Output_data_nmos_slow_mat[0][i][j] = (double) Vds/256 * 4.096 * 3;
			//Storing Vds into array
            
            ADC_SAR_1_StartConvert();
            ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
			//waiting until conversion is over
            ADC_SAR_1_StopConvert();
            Output_data_nmos_slow_mat[1][i][j] = ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16()/100);
			//Storing Id into array
            j++; //incrementing array count
        }
        i++; //incrementing array count
    }
    return 0;
}


int main(void)
{
    //Enabling VDACs and ADCs
    VDAC8_GS_Start();
    VDAC8_DS_Start();
    ADC_SAR_1_Start();
    int return_code;
    
    double Output_data_nmos[2][CURVE_NUM][VDAC_DS_MAX/VD_STEP_NMOS + 1];
    
    
    for(;;)
    {
        return_code = 
    }
}
/* [] END OF FILE */
