/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#define Vds_step_slow 1
#define Vds_step_fast 5
#define VDAC_GS_MAX 255
#define VDAC_DS_MAX 188
#define ID_MAX 4000
#define ID_TH 200

unsigned char eight_bit_unsigned_round(double x)
{
    unsigned char x_round;
    x_round = (unsigned char) (x + 0.5);
    return x_round;
}


//Finds Vth by sorting through Vgs's until a minumum current of 1 mA is found
//Id is found by a 1 Ohm series resistor whose potential difference is magnitifed 200 fold
//For accurate reading
unsigned short vgs_th_find()
{
    unsigned char   Vgs;
    unsigned char   Vds = 21; //Vds_real = Vds/256 * 4.096 * 3 (OpAmp gain)
    double          Id;
    
    VDAC8_DS_SetValue(Vds); //Set Vds to 1 Volt
    for(Vgs = 0; Vgs < VDAC_GS_MAX; Vgs++)
    {
        VDAC8_GS_SetValue(Vgs);
        ADC_SAR_1_StartConvert();
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
        ADC_SAR_1_StopConvert();
        Id = ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16()); //Returns mV of the OpAmp output (200x real Id)
        if(Id > ID_TH)
        {
            return Vgs;
        }
    }
    return 64;
}

//Finds the MAX current 20mA, Id is found through a 1 Ohm series resistor who
// potential difference is magnified 200 fold for accurate reading
//Therefor ID_MAX = 20*200 == 4000
unsigned short vgs_max_id_find(unsigned char Vth)
{
    unsigned char   Vgs;
    double          Id;
    
    VDAC8_DS_SetValue(VDAC_DS_MAX); ////Sets Vds = 188/256 * 4.096 * 3 (max Vds to test wtih) to find max current
    for(Vgs = Vth; Vgs < VDAC_GS_MAX; Vgs++)
    {
        //Run through Vgs values until we hit max current of 20mA with max Vds
        VDAC8_GS_SetValue(Vgs);
        ADC_SAR_1_StartConvert();
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
        ADC_SAR_1_StopConvert();
        Id = ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16());
        if (Id >= ID_MAX)
        {
            break;
        }
    }
    return Vgs;
}


int nmos_sweep_slow()
{
    //returning a pointer to the array because C doesn't allow the 
    //returning of arrays.
    unsigned char   i=0;
    unsigned char   j=1;
    unsigned char   k;
    unsigned char   Vds;
    int             ADC_code;
    unsigned short  Vgs_th;
    unsigned char   Vgs_max;
    double          Output_data_nmos_slow_mat[2][6][VDAC_DS_MAX/Vds_step_slow + 1] = {0};
    unsigned char   Vgs_test_points[6]={0};
    double          Vgs_gain;
    double          Vgs_step;
    Vgs_th = vgs_th_find();
    if(Vgs_th > 255)
    {
        return 1;
    }
    
    Vgs_max = vgs_max_id_find(Vgs_th); //Vgs max is the Vgs that pulls 20 mA
    
    //Doing a linspace between Vth and Vgs_max (the Vgs that pulls 20 mA) for testing points
    
    Vgs_step = (Vgs_max - Vgs_th)/6.0;
    for (k = 0; k < 6; k++)
    {
        if(Vgs_th + k*Vgs_step > VDAC_GS_MAX)
        {
            break;
        }
        Vgs_test_points[k] = eight_bit_unsigned_round(Vgs_th + k*Vgs_step);    
    }
    
    
    for(k=0; k < 6; k++)
    {
        if ((k > 0) && (Vgs_test_points[k] == Vgs_test_points[k-1]))
        {
            //Skips a value if it's the same as the previous
            continue;
        } else if((k > 0) && Vgs_test_points[k] == 0)
        {
            break;
        }
        VDAC8_GS_SetValue(Vgs_test_points[k]);
        for(Vds = 0;Vds <= VDAC_DS_MAX; Vds += Vds_step_slow)
        {
            VDAC8_DS_SetValue(Vds);
            
            Output_data_nmos_slow_mat[0][i][0] = ((Vgs_test_points[k])/255.0*4.096);
            Output_data_nmos_slow_mat[1][i][0] = Output_data_nmos_slow_mat[0][i][0];
            
            Output_data_nmos_slow_mat[0][i][j] = (double) Vds/256 * 4.096 * 3;
            
            ADC_SAR_1_StartConvert();
            ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
            ADC_SAR_1_StopConvert();
            Output_data_nmos_slow_mat[1][i][j] = ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16()); // RIP PSoC MAY ALEN HAVE MERCY ON OUR SOULS
            j++;
        }
        i++;
    }
    return 0;
}


int main(void)
{
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    VDAC8_GS_Start();
    VDAC8_DS_Start();
    ADC_SAR_1_Start();
    int return_code;
    
    for(;;)
    {
        return_code = nmos_sweep_slow();
    }
}

/* [] END OF FILE */
