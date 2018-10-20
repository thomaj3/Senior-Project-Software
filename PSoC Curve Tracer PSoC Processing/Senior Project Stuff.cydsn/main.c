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
#define VDAC_GS_MAX 255
#define VDAC_DS_MAX 188

unsigned short vgs_th_find()
{
    unsigned char Vgs;
    unsigned char Vds = 50;
    int ADC_code;
    double Id;
    double Id_th = 20;
    
    VDAC8_DS_SetValue(Vds);
    for(Vgs = 0; Vgs <= VDAC_GS_MAX; Vgs++)
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

double *nmos_sweep_slow()
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
    double *Output_data;
    Vgs_th = vgs_th_find();
    if(Vgs_th > 255)
    {
        strcpy(error_msg, "No Vgs_th Found");
        //DisplayText(error_msg);
        return 0;
    }
    
    
    Vgs_test_points[0] = (unsigned char) Vgs_th/2;
    Vgs_test_points[1] = (unsigned char) 4*Vgs_th/5;
    Vgs_test_points[2] = (unsigned char) Vgs_th;
    Vgs_test_points[3] = (unsigned char) 6*Vgs_th/5;
    Vgs_test_points[4] = (unsigned char) 2*Vgs_th;
    Vgs_test_points[5] = (unsigned char) 3*Vgs_th;
    //Test at Vgs 1/2, 4/5, 1, 6/5, 2, and 3 times the threshold voltage
    
    
    /*
    for(Vgs = 0; Vgs < VDAC_GS_MAX ; Vgs += Vgs_step)
    {
        VDAC8_GS_SetValue(Vgs);
        for(Vds = 0;Vds <= VDAC_DS_MAX; Vds += Vds_step_slow)
        {
            VDAC8_DS_SetValue(Vds);
            
            Output_data_nmos_slow_mat[0][i][0] = (double) Vgs;
            Output_data_nmos_slow_mat[1][i][0] = (double) Vgs;
            
            Output_data_nmos_slow_mat[0][i][j] = (double) Vds/256 * 4.096 * 3;
            
            ADC_SAR_1_StartConvert();
            ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
            ADC_code = ADC_SAR_1_GetResult16();
            ADC_SAR_1_StopConvert();
            Output_data_nmos_slow_mat[1][i][j] = (double) ADC_SAR_1_CountsTo_mVolts(ADC_code);
            j++;
        }
        i++;
    }
    */
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
            Output_data_nmos_slow_mat[1][i][j] = (double) ADC_SAR_1_CountsTo_mVolts(ADC_code);
            j++;
        }
        i++;
    }
    /*
    for(Vgs = Vgs_th - 10; Vgs < Vgs_th + 11; Vgs += Vgs_th + 10 ) 
    {
        VDAC8_GS_SetValue(Vgs);
        for(Vds = 0;Vds <= VDAC_DS_MAX; Vds += Vds_step_slow)
        {
            VDAC8_DS_SetValue(Vds);
            
            Output_data_nmos_slow_mat[0][i][0] = (double) Vgs;
            Output_data_nmos_slow_mat[1][i][0] = (double) Vgs;
            
            Output_data_nmos_slow_mat[0][i][j] = (double) Vds/256 * 4.096 * 3;
            
            ADC_SAR_1_StartConvert();
            ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
            ADC_code = ADC_SAR_1_GetResult16();
            ADC_SAR_1_StopConvert();
            Output_data_nmos_slow_mat[1][i][j] = (double) ADC_SAR_1_CountsTo_mVolts(ADC_code);
            j++;
        }
        i++;    
    }
    */
    
    
    Output_data = &Output_data_nmos_slow_mat[0][0][0];
    return Output_data;
}

int threedim_matrix_element_retrival(int *pointer, int row_size, int column_size, int depth_index, int row_index, int column_index)
{
    return *(pointer + ( (row_size * column_size * depth_index) + (column_size * row_index) + column_index));
    //Because 3d arrays are stored "one-dimensionally" they can be accessed by a single pointer
    //This pointer however has to be adjusted according to the dimensions of the array as well as index
}

int main(void)
{
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    VDAC8_GS_Start();
    VDAC8_DS_Start();
    ADC_SAR_1_Start();
    double *data;
    
    for(;;)
    {
        data = nmos_sweep_slow();
    }
}

/* [] END OF FILE */
