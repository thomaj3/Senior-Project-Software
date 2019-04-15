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

void ui_control(uint16_t x, uint16_t y)
{
    //switch statement that controls the touchscreen
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
            if(x>=0 && x<=159 && y>=0 && y<=119)
            {
                draw_options_averages_screen(); 
            }
            if(x>=160 && x<=319 && y>=0 && y<=119)
            {
                draw_coordinates();
            }
            break;
        case PLOT_SCREEN :
            if(x>=130 && x<=190 && y>=209 && y<=239)
            {
                draw_choose_screen();  
            }
            break;
        case OPTION_AVERAGES_SCREEN :
            if(x>=0 && x<=50 && y>=0 && y<=30)
            {
                draw_options_screen();  
            }
            break;
        case OPTION_SD_SCREEN :
            if(x>=0 && x<=50 && y>=0 && y<=30)
            {
                draw_options_screen();  
            }
            break;
        case OPTION_CURVES_SCREEN :
            if(x>=0 && x<=50 && y>=0 && y<=30)
            {
                draw_options_screen();  
            }
            break;
        case OPTION_SETTLING_SCREEN :
            if(x>=0 && x<=50 && y>=0 && y<=30)
            {
                draw_options_screen();  
            }
            break;
        case DEBUG_SCREEN :
            if(x>=0 && x<=50 && y>=0 && y<=30)
            {
                draw_choose_screen();  
                screen_state = DEVICE_SELECTION_SCREEN;
            }
            else
            {
                fill_rect(95,95,30,30,BLACK);
            
                char x_touch[10];
                char y_touch[10];

                itoa(x, x_touch, 10);
                itoa(y, y_touch, 10);
                
                draw_string(100,110,WHITE,x_touch);
                draw_string(100,100,WHITE,y_touch);
            }
            break;
    }
}