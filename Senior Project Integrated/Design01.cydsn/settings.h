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
#define VD_STEP_NMOS  1
//#define VD_STEP_PMOS  1
//#define VC_STEP_NPN   1
//#define VC_SEPT_PNP   1
//choose the amount of steps Vd/Vc will use. There will be (255/VD_step + 1) steps
//must be divisble of 255 i.e. 1,3,5,15,17,51,85,255
#define CURVE_NUM           4       //Number of curves to plot DO NOT USE MORE THAN 6
#define ID_MAX              20      //Max allowable current. Enter the desired current in mA
#define ID_TH               1       //Current to define on state at 1 V Vds. Enter the desired current in mA
#define SETTLING_WAIT_TIME  1       //How many milliseconds to wait for the DUT to settle under DAC levels before starting ADC conversion
#define AVG                 1000

/* [] END OF FILE */