// Steven Andresen
// Senior Project Spring 2019

#include "project.h"
#include "font.h"
#include "screen.h"
#include "strings.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
// How to read
//  // Character, integer code
//  # of array indecies to next number

//  # of pixels in line 0, 
//	(index of pixels from 0-4),
//	# of pixels in line 1...

//  //Number...

static const uint8_t font[] = 
{
    // Font Height
    7,
    
    // 0, 0
    26,
    
    3,
    1,2,3,
    2,
    0,4,
    3,
    0,1,4,
    3,
    0,2,4,
    3,
    0,3,4,
    2,
    0,4,
    3,
    1,2,3,
    
    // 1, 1
    19,
    
    5,
    0,1,2,3,4,
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    2,
    2,
    1,2,
    1,
    2,
    
    // 2, 2
    23,
    
    5,
    0,1,2,3,4,
    2,
    0,4,
    1,
    1,
    2,
    2,3,
    1,
    4,
    2,
    0,4,
    3,
    1,2,3,
    
    // 3, 3
    21,
    
    3,
    1,2,3,
    2,
    0,4,
    1,
    4,
    2,
    2,3,
    1,
    4,
    2,
    0,4,
    3,
    1,2,3,
    
    // 4, 4
    22,
    
    1,
    4,
    1,
    4,
    5,
    0,1,2,3,4,
    2,
    0,4,
    2,
    1,4,
    2,
    2,4,
    2,
    3,4,
    
    // 5, 5
    24,
    
    3,
    1,2,3,
    2,
    0,4,
    1,
    4,
    1,
    4,
    4,
    0,1,2,3,
    1,
    0,
    5,
    0,1,2,3,4,
    
    // 6, 6
    22,
    
    3,
    1,2,3,
    2,
    0,4,
    2,
    0,4,
    4,
    0,1,2,3,
    1,
    0,
    1,
    1,
    2,
    2,3,
    
    // 7, 7
    19,
    
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    3,
    1,
    4,
    2,
    0,4,
    5,
    0,1,2,3,4,
    
    // 8, 8
    24,
    
    3,
    1,2,3,
    2,
    0,4,
    2,
    0,4,
    3,
    1,2,3,
    2,
    0,4,
    2,
    0,4,
    3,
    1,2,3,
    
    // 9, 9
    22,
    
    2,
    1,2,
    1,
    3,
    1,
    4,
    4,
    1,2,3,4,
    2,
    0,4,
    2,
    0,4,
    3,
    1,2,3,
    
    // A, 10
    25,
    
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    5,
    0,1,2,3,4,
    2,
    0,4,
    3,
    1,2,3,
    
    // B, 11
    27,
    
    4,
    0,1,2,3,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    4,
    0,1,2,3,
    2,
    0,4,
    4,
    0,1,2,3,
    
    // C, 12
    20,
    
    3,
    1,2,3,
    2,
    0,4,
    1,
    0,
    1,
    0,
    1,
    0,
    2,
    0,4,
    3,
    1,2,3,
    
    // D, 13
    25,
    
    4,
    0,1,2,3,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    4,
    0,1,2,3,
    
    // E, 14
    25,
    
    5,
    0,1,2,3,4,
    1,
    0,
    1,
    0,
    4,
    0,1,2,3,
    1,
    0,
    1,
    0,
    5,
    0,1,2,3,4,
    
    // F, 15
    20,
    
    1,
    0,
    1,
    0,
    1,
    0,
    1,
    0,
    3,
    0,1,2,
    1,
    0,
    5,
    0,1,2,3,4,
    
    // G, 16
    24,
    
    3,
    1,2,3,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    3,
    0,3,4,
    1,
    0,
    4,
    1,2,3,4,
    
    // H, 17
    24,
    
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    5,
    0,1,2,3,4,
    2,
    0,4,
    2,
    0,4,
    
    // I, 18
    18,
    
    3,
    1,2,3,
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    2,
    3,
    1,2,3,
    
    // J, 19
    17,
    
    3,
    1,2,3,
    2,
    0,4,
    1,
    4,
    1,
    4,
    1,
    4,
    1,
    4,
    1,
    4,
    
    // K, 20
    22,
    
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,3,
    3,
    0,1,2,
    2,
    0,3,
    2,
    0,4,
    
    // L, 21
    18,
    
    5,
    0,1,2,3,4,
    1,
    0,
    1,
    0,
    1,
    0,
    1,
    0,
    1,
    0,
    1,
    0,
    
    // M, 22
    24,
    
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    3,
    0,2,4,
    4,
    0,1,3,4,
    2,
    0,4,
    
    // N, 23
    24,
    
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    3,
    0,3,4,
    3,
    0,2,4,
    3,
    0,1,4,
    2,
    0,4,
    
    // O, 24
    23,
    
    3,
    1,2,3,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    3,
    1,2,3,
    
    // P, 25
    21,
    
    1,
    0,
    1,
    0,
    1,
    0,
    1,
    0,
    4,
    0,1,2,3,
    2,
    0,4,
    4,
    0,1,2,3,
    
    // Q, 26
    23,
    
    3,
    1,2,4,
    2,
    0,3,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    3,
    1,2,3,
    
    // R, 27
    25,
    
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    4,
    0,1,2,3,
    2,
    0,4,
    4,
    0,1,2,3,
    
    // S, 28
    22,
    
    3,
    1,2,3,
    2,
    0,4,
    1,
    4,
    1,
    4,
    3,
    1,2,3,
    1,
    0,
    4,
    1,2,3,4,
    
    // T, 29
    18,
    
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    2,
    5,
    0,1,2,3,4,
    
    // U, 30
    22,
    
    3,
    1,2,3,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    
    // V, 31
    20,
    
    1,
    2,
    2,
    1,3,
    2,
    1,3,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    
    // W, 32
    24,
    
    2,
    0,4,
    4,
    0,1,3,4,
    3,
    0,2,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    
    // X, 33
    20,
    
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    2,
    1,3,
    1,
    2,
    2,
    1,3,
    2,
    0,4,
    
    // Y, 34
    16,
    
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    2,
    2,
    1,3,
    2,
    0,4,
    
    // Z, 35
    22,
    
    5,
    0,1,2,3,4,
    1,
    0,
    1,
    1,
    1,
    2,
    1,
    3,
    1,
    4,
    5,
    0,1,2,3,4,
    
    // ., 36
    8,
    
    1,
    2,
    0,

    0,

    0,

    0,

    0,

    0,
    
    // [space], 37
    7,
    
    0,
    
    0,
    
    0,
    
    0,
    
    0,
    
    0,
    
    0
};

// Work in progress
void draw_character(int16_t x, int16_t y, uint16_t color, uint16_t character)
{
    uint16_t index = 1;
    
    for(int i=0; i<character;i++)
    {
        index = index + font[index] + 1;
    }
    
    index = index+1;
    y = y-2;
    x = x-2;
    uint8_t height = font[0];
    
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<font[index] ;j++)
        {
            draw_pixel(x+font[index+j+1],y,color);
        }
        y = y+1;
        index = index+font[index]+1;
    }
}

void draw_string(int16_t x, int16_t y, uint16_t color, char string[])
{
    int16_t x_coor = x;
    
    while(*string != 0)
    {
        char g = *string;
        
        switch(g)
        {
            case 48 : 
                draw_character(x_coor,y,color,0); // Draws 0
                break;
            case 49 : 
                draw_character(x_coor,y,color,1); // Draws 1
                break;
            case 50 : 
                draw_character(x_coor,y,color,2); // Draws 2
                break;
            case 51 : 
                draw_character(x_coor,y,color,3); // Draws 3
                break;
            case 52 : 
                draw_character(x_coor,y,color,4); // Draws 4
                break;
            case 53 : 
                draw_character(x_coor,y,color,5); // Draws 5
                break;
            case 54 : 
                draw_character(x_coor,y,color,6); // Draws 6
                break;
            case 55 : 
                draw_character(x_coor,y,color,7); // Draws 7
                break;
            case 56 : 
                draw_character(x_coor,y,color,8); // Draws 8
                break;
            case 57 : 
                draw_character(x_coor,y,color,9); // Draws 9
                break;
            case 65 : 
                draw_character(x_coor,y,color,10); // Draws A
                break;
            case 66 : 
                draw_character(x_coor,y,color,11); // Draws B
                break;
            case 67 : 
                draw_character(x_coor,y,color,12); // Draws C
                break;
            case 68 : 
                draw_character(x_coor,y,color,13); // Draws D
                break;
            case 69 : 
                draw_character(x_coor,y,color,14); // Draws E
                break;
            case 70 : 
                draw_character(x_coor,y,color,15); // Draws F
                break;
            case 71 : 
                draw_character(x_coor,y,color,16); // Draws G
                break;
            case 72 :
                draw_character(x_coor,y,color,17); // Draws H
                break;
            case 73 :
                draw_character(x_coor,y,color,18); // Draws I
                break;
            case 74 :
                draw_character(x_coor,y,color,19); // Draws J
                break;
            case 75 :
                draw_character(x_coor,y,color,20); // Draws K
                break;
            case 76 : 
                draw_character(x_coor,y,color,21); // Draws L
                break;
            case 77 :
                draw_character(x_coor,y,color,22); // Draws M
                break;
            case 78 :
                draw_character(x_coor,y,color,23); // Draws N
                break;
            case 79 :
                draw_character(x_coor,y,color,24); // Draws O
                break;
            case 80 :
                draw_character(x_coor,y,color,25); // Draws P
                break;
            case 81 :
                draw_character(x_coor,y,color,26); // Draws Q
                break;
            case 82 :
                draw_character(x_coor,y,color,27); // Draws R
                break;
            case 83 :
                draw_character(x_coor,y,color,28); // Draws S
                break;
            case 84 :
                draw_character(x_coor,y,color,29); // Draws T
                break;
            case 85 :
                draw_character(x_coor,y,color,30); // Draws U
                break;
            case 86 :
                draw_character(x_coor,y,color,31); // Draws V
                break;
            case 87 :
                draw_character(x_coor,y,color,32); // Draws W
                break;
            case 88 :
                draw_character(x_coor,y,color,33); // Draws X
                break;
            case 89 :
                draw_character(x_coor,y,color,34); // Draws Y
                break;
            case 90 :
                draw_character(x_coor,y,color,35); // Draws Z
                break;
            case 46 :
                draw_character(x_coor,y,color,36); // Draws .
                break;
            case 32 :
                draw_character(x_coor,y,color,37); // Draws [space]
                break;
        }
        
        x_coor = x_coor+7;
        if (x_coor>316)
        {
            x_coor = x;
            y = y-9;
        }
        
        string = string+1;
    }
}

void draw_number(int16_t x, int16_t y, uint16_t color, double number)
{
    number = number+0.0005;
    
    int tens        = (int)(number/10);
    int ones        = (int)(number-(tens*10));
    int tenths      = (int)((number-((tens*10)+ones))*10);
    int hundredths  = (int)((number-((tens*10)+ones+(tenths*0.1)))*100);
    int thousandths = (int)((number-((tens*10)+ones+(tenths*0.1)+(hundredths*0.01)))*1000);
    
    int x_offset;
    
    if(tens != 0)
    {
        draw_character(x,y,color,tens);
        x_offset = 7;
    }
    
    if(tens == 0)
    {
        x_offset = 0;
    }
    
    draw_character(x+x_offset,y,color,ones);
    draw_character(x+x_offset+7,y,color,36);
    draw_character(x+x_offset+14,y,color,tenths);
    draw_character(x+x_offset+21,y,color,hundredths);
    draw_character(x+x_offset+28,y,color,thousandths);
}

void draw_coordinates(double y_max)
{
    int y_max_int = (int) (y_max);
    int y_max_pixel = (int) 240/(1.25);
    double y_label;
    int x_label;
    char string_throwaway_y[10];
    char string_throwaway_x[4]; //= NULL;
    //string_print = malloc(sizeof(**string_print)*3);
    int y_max_step = y_max_pixel/4;
    int x_max_step = 169/4;
    int i;
    int k;
    draw_line(0,0,190,0,WHITE);
    draw_line(0,0,0,y_max_pixel,WHITE);
    
    for(i=1;i<5;i++)
    {
        y_label =  ((y_max/1.25))/4.0 * i;
        sprintf(string_throwaway_y,"%.1f", y_label);
        sprintf(string_throwaway_x,"%i", i*2);
        draw_line(0,i*y_max_step,5,i*y_max_step,WHITE);
        draw_string(12,i*y_max_step,WHITE,string_throwaway_y);
        draw_line(i*x_max_step,0,i*x_max_step,3,WHITE);
        draw_string(i*x_max_step,12,WHITE,string_throwaway_x);
    }
    
}