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
    switch(screen_state)
    {
        case DEVICE_SELECTION_SCREEN :
            if(x>=35 && x<=283 && y>=111 && y<=129)             //Debug center white
            {
                fill_screen(BLACK);
                
                screen_state = 1;
                
                char x_touch[10];
                char y_touch[10];

                itoa(x, x_touch, 10);
                itoa(y, y_touch, 10);
                
                draw_string(100,110,WHITE,x_touch);
                draw_string(100,100,WHITE,y_touch);
                
                draw_string(100,200,WHITE,"TOUCH COORDINATES");
                
                fill_rect(0,0,50,30,WHITE);
                
                draw_string(10,15,BLACK,"RETURN");
            }
            else if(x>=10 && x<=149 && y>=10 && y<=109)         //N-type FET
            {
                device_selection = NMOS;
            }
            else if(x>=10 && x<=149 && y>=131 && y<=230)        //NPN
            {
                device_selection = NPN;         
            }
            else if(x>=171 && x<=310 && y>=10 && y<=109)        //P-type FET
            {
                device_selection = PMOS;         
            }
            else if(x>=171 && x<=310 && y>=131 && y<=230)        //PNP
            {
                device_selection = PNP;         
            }
            break;
        case PLOT_SCREEN :
            if(x>=130 && x<=190 && y>=209 && y<=239)
            {
                screen_state = 0;  
            }
            break;
    }
}