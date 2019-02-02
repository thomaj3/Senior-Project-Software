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
#define VD_STEP_PMOS  1
#define VC_STEP_NPN   1
#define VC_SEPT_PNP   1
//choose a for how many steps will be 255/VD_step + 1 steps
//must be divisble of 255 i.e. 1,3,5,15,17,51,85,255
#define CURVE_NUM     6        //Number of curves to plot
#define ID_MAX        2000     //Max allowable current. Enter 100-fold the desired current in mA
#define ID_TH         50       //Current to define on state at 1 V Vds. Enter 100-fold the desired current in mA

/* [] END OF FILE */