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
#define Vgs_step 51
#define Vds_step_slow 1
#define Vds_step_fast 5
#define VDAC_GS_MAX 188
#define VDAC_DS_MAX 188

unsigned char eight_bit_unsigned_round(double x)
{
    x = (unsigned char) (x + 0.5);
    return x;
}

unsigned short vgs_th_find()
{
    unsigned char Vgs;
    unsigned char Vds = 50;
    int ADC_code;
    double Id;
    double Id_th = 20;
    
    VDAC8_DS_SetValue(Vds);
    for(Vgs = 0; Vgs < VDAC_GS_MAX; Vgs++)
    {
        VDAC8_GS_SetValue(Vgs);
        ADC_SAR_1_StartConvert();
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
        ADC_SAR_1_StopConvert();
        ADC_code = ADC_SAR_1_GetResult16();
        Id = ADC_SAR_1_CountsTo_mVolts(ADC_code);
        if(Id > Id_th)
        {
            return Vgs;    
        }
    }
    return 256;
}

int nmos_sweep_slow()
{
    //returning a pointer to the array because C doesn't allow the 
    //returning of arrays.
    unsigned char i=0;
    unsigned char j=1;
    unsigned char k;
    unsigned char Vds;
    int ADC_code;
    unsigned short Vgs_th;
    char error_msg[16];
    double Output_data_nmos_slow_mat[2][6][VDAC_DS_MAX/Vds_step_slow + 1];
    //Because local variables die after being called, the array has to be static or else
    //the returning pointer will point to junk
    unsigned char Vgs_test_points[6];
    Vgs_th = vgs_th_find();
    double Vgs_gain;
    if(Vgs_th > 255)
    {
        return 1;
    }
    
    for(Vgs_gain = 3.0; Vgs_gain*Vgs_th > 255; Vgs_gain -= 0.5)
    {
        if(Vgs_gain <= 1)
        {
            break;
        }
    }
    if (Vgs_gain > 1)
    {
        Vgs_test_points[0] = eight_bit_unsigned_round((Vgs_gain/6.0)*Vgs_th); 
        Vgs_test_points[1] = eight_bit_unsigned_round((2*Vgs_gain/9)*Vgs_th);
        Vgs_test_points[2] = Vgs_th;
        Vgs_test_points[3] = eight_bit_unsigned_round((4*Vgs_gain/9)*Vgs_th);
        Vgs_test_points[4] = eight_bit_unsigned_round((6*Vgs_gain/9)*Vgs_th);
        Vgs_test_points[5] = eight_bit_unsigned_round(Vgs_gain*Vgs_th);
    } else
    {
        Vgs_test_points[0] = Vgs_th;
    }
    if(Vgs_test_points[0] == Vgs_th)
    {
        VDAC8_GS_SetValue(Vgs_test_points[0]);
        for(Vds = 0;Vds <= VDAC_DS_MAX; Vds += Vds_step_slow)
        {
            VDAC8_DS_SetValue(Vds);
            
            Output_data_nmos_slow_mat[0][i][0] = (double) Vgs_test_points[0];
            Output_data_nmos_slow_mat[1][i][0] = (double) Vgs_test_points[0];
            
            Output_data_nmos_slow_mat[0][i][j] = (double) Vds/256 * 4.096 * 3;
            
            ADC_SAR_1_StartConvert();
            ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
            ADC_code = ADC_SAR_1_GetResult16();
            ADC_SAR_1_StopConvert();
            Output_data_nmos_slow_mat[1][i][j] = ADC_SAR_1_CountsTo_mVolts(ADC_code);
            j++;
        }
        return 2;
    }
    else
    {
        for(k=0; k < 6; k++)
        {
            VDAC8_GS_SetValue(Vgs_test_points[k]);
            for(Vds = 0;Vds <= VDAC_DS_MAX; Vds += Vds_step_slow)
            {
                VDAC8_DS_SetValue(Vds);
                
                Output_data_nmos_slow_mat[0][i][0] = (double) Vgs_test_points[k];
                Output_data_nmos_slow_mat[1][i][0] = (double) Vgs_test_points[k];
                
                Output_data_nmos_slow_mat[0][i][j] = (double) Vds/256 * 4.096 * 3;
                
                ADC_SAR_1_StartConvert();
                ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
                ADC_code = ADC_SAR_1_GetResult16();
                ADC_SAR_1_StopConvert();
                Output_data_nmos_slow_mat[1][i][j] = ADC_SAR_1_CountsTo_mVolts(ADC_code);
                j++;
            }
            i++;
        }
        return 0;
    }
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
