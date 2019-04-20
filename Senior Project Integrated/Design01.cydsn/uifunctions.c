#include "project.h"
#include "screen.h"
#include "font.h"
#include "strings.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "font.h"
#include "uifunctions.h"

int screen_state;
int device_selection;
int curve_nums;
int write_sd;
int num_avg;

void ui_control(uint16_t x, uint16_t y)
{
    //switch statement that controls the touchscreen
    //if statements outline rectangular coordinates for button presses
    switch(screen_state)
    {
        case DEVICE_SELECTION_SCREEN :
            if(x>=35 && x<=283 && y>=111 && y<=129)             //Debug center white
            {
                draw_debug_screen(x, y);
            }
            else if(x>=10 && x<=149 && y>=10 && y<=109)         //N-type FET
            {
                device_selection = NMOS;
                draw_options_screen();
            }
            else if(x>=10 && x<=149 && y>=131 && y<=230)        //NPN
            {
                device_selection = NPN;    
                draw_options_screen();
            }
            else if(x>=171 && x<=310 && y>=10 && y<=109)        //P-type FET
            {
                device_selection = PMOS;     
                draw_options_screen();
            }
            else if(x>=171 && x<=310 && y>=131 && y<=230)        //PNP
            {
                device_selection = PNP;  
                draw_options_screen();
            }
            break;
        case OPTIONS_SCREEN :
            if(x>=0 && x<=119 && y>=0 && y<=119)                //button for number of averages options
            {
                draw_options_averages_screen(); 
            }
            else if(x>=0 && x<=119 && y>=121 && y<=239)         //button for sd card options
            {
                draw_options_sd_screen(); 
            }
            else if(x>=121 && x<=240 && y>=0 && y<=119)         //button for number of curves options
            {
                draw_options_curves_screen(); 
            }
            else if(x>=121 && x<=240 && y>=121 && y<=239)       //button for settling time options
            {
                draw_options_settling_screen(); 
            }
            else if(x>=241 && x<=319 && y>=0 && y<=119)         //return button
            {
                draw_choose_screen();
            }
            else if(x>=241 && x<=319 && y>=121 && y<=239)       //run test button
            {
                draw_coordinates();
            }
            break;
        case PLOT_SCREEN :
            if(x>=130 && x<=190 && y>=209 && y<=239)            //stop/return button
            {
                draw_choose_screen();  
            }
            break;
        case OPTION_AVERAGES_SCREEN :
            if(x>=241 && x<=319 && y>=0 && y<=239)         //return button
            {
                draw_options_screen();
            }
            else if(x>=80 && x<=150 && y>=150 && y<=200)  //+1
            {
                num_avg = num_avg+1;
                if(num_avg>1000)
                {
                    num_avg = 1000;
                }
                fill_rect(10,95,60,30,BLACK);
                
                char avg_num[4];
                itoa(num_avg, avg_num, 10);
                
                draw_string(20,105,WHITE,avg_num,2);
            }
            else if(x>=80 && x<=150 && y>=80 && y<=130)   //+10                 
            {
                num_avg = num_avg+10;
                if(num_avg>1000)
                {
                    num_avg = 1000;
                }
                fill_rect(10,95,60,30,BLACK);
                
                char avg_num[4];
                itoa(num_avg, avg_num, 10);
                
                draw_string(20,105,WHITE,avg_num,2);
            }
            else if(x>=80 && x<=150 && y>=10 && y<=60)  //+100                  
            {
                num_avg = num_avg+100;
                if(num_avg>1000)
                {
                    num_avg = 1000;
                }
                fill_rect(10,95,60,30,BLACK);
                
                char avg_num[4];
                itoa(num_avg, avg_num, 10);
                
                draw_string(20,105,WHITE,avg_num,2);
            }
            else if(x>=160 && x<=230 && y>=150 && y<=200)  //-1
            {
                num_avg = num_avg-1;
                if(num_avg<1)
                {
                    num_avg = 1;
                }
                fill_rect(10,95,60,30,BLACK);
                
                char avg_num[4];
                itoa(num_avg, avg_num, 10);
                
                draw_string(20,105,WHITE,avg_num,2);
            }
            else if(x>=160 && x<=230 && y>=80 && y<=130)   //-10                 
            {
                num_avg = num_avg-10;
                if(num_avg<1)
                {
                    num_avg = 1;
                }
                fill_rect(10,95,60,30,BLACK);
                
                char avg_num[4];
                itoa(num_avg, avg_num, 10);
                
                draw_string(20,105,WHITE,avg_num,2);
            }
            else if(x>=160 && x<=230 && y>=10 && y<=60)  //-100                  
            {
                num_avg = num_avg-100;
                if(num_avg<1)
                {
                    num_avg = 1;
                }
                fill_rect(10,95,60,30,BLACK);
                
                char avg_num[4];
                itoa(num_avg, avg_num, 10);
                
                draw_string(20,105,WHITE,avg_num,2);
            }
            break;
        case OPTION_SD_SCREEN :
            if(x>=241 && x<=319 && y>=0 && y<=239)         //return button
            {
                draw_options_screen();
            }
            else if(x>=30 && x<=110 && y>=100 && y<=150)        //yes button
            {
                draw_button(30,100,80,50,LIGHTBLUE,BLACK,"YES");  
                draw_button(130,100,80,50,WHITE,BLACK,"NO");
                write_sd = 1;
            }
            else if(x>=130 && x<=210 && y>=100 && y<=150)       //no button
            {
                draw_button(30,100,80,50,WHITE,BLACK,"YES");  
                draw_button(130,100,80,50,LIGHTBLUE,BLACK,"NO");
                write_sd = 0;
            }
            break;
        case OPTION_CURVES_SCREEN :
            if(x>=241 && x<=319 && y>=0 && y<=239)         //return button
            {
                draw_options_screen();
            }
            else if(x>=130 && x<=200 && y>=30 && y<=100)                  
            {
                if(curve_nums>1)
                {
                    curve_nums--;
                }
                else
                {
                    curve_nums = 1;
                }
                fill_rect(40,95,60,30,BLACK);
                
                char num_curve[2];
                itoa(curve_nums, num_curve, 10);
                
                draw_string(50,105,WHITE,num_curve,3);
            }
            else if(x>=130 && x<=200 && y>=120 && y<=190)                  //return button
            {
                if(curve_nums<8)
                {
                    curve_nums++;
                }
                else
                {
                    curve_nums = 8;
                }
                fill_rect(40,95,60,30,BLACK);
                
                char num_curve[2];
                itoa(curve_nums, num_curve, 10);
                
                draw_string(50,105,WHITE,num_curve,3);
            }
            break;
        case OPTION_SETTLING_SCREEN :
            if(x>=241 && x<=319 && y>=0 && y<=239)         //return button
            {
                draw_options_screen();
            }
            break;
        case DEBUG_SCREEN :
            if(x>=0 && x<=50 && y>=0 && y<=30)                  //return button
            {
                draw_choose_screen();  
                screen_state = DEVICE_SELECTION_SCREEN;
            }
            else                                                //draws coordinates of touch
            {
                fill_rect(95,95,30,30,BLACK);
            
                char x_touch[10];
                char y_touch[10];

                itoa(x, x_touch, 10);
                itoa(y, y_touch, 10);
                
                draw_string(100,110,WHITE,x_touch,1);
                draw_string(100,100,WHITE,y_touch,1);
            }
            break;
    }
}