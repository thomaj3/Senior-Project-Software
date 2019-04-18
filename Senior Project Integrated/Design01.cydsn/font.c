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
//	(index of pixels to draw from 0-4),
//	# of pixels in line 1...

//  // Character, integer code...

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

void draw_character(int16_t x, int16_t y, uint16_t color, uint16_t character, uint8_t font_scale)
{
    uint16_t index = 1;
    
    //moves index pointer to proper index in font array
    for(int i=0; i<character;i++)
    {
        index = index + font[index] + 1;
    }
    
    index = index+1;
    y = y-2*font_scale;
    x = x-2*font_scale;
    uint8_t height = font[0];
    
    //reads through array, and changes pixels to ddraw character
//    for(int i=0; i<height; i++)
//    {
//        for(int j=0; j<font[index]; j++)
//        {
//            draw_pixel(x+font[index+j+1],y,color);
//        }
//        y = y+1;
//        index = index+font[index]+1;
//    }
    
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<font[index]; j++)
        {
            fill_rect(x+font[index+j+1]*font_scale,y+(i*(font_scale-1)),font_scale,font_scale, color);
        }
        y = y+1;
        index = index+font[index]+1;
    }
}

void draw_string(int16_t x, int16_t y, uint16_t color, char string[], uint8_t font_scale)
{
    int16_t x_coor = x;
    
    if(font_scale<1 || font_scale>8)
    {
        font_scale = 1;   
    }
    
    while(*string != 0)
    {
        char g = *string;
        
        switch(g)
        {
            case 48 : 
                draw_character(x_coor,y,color,0,font_scale); // Draws 0
                break;
            case 49 : 
                draw_character(x_coor,y,color,1,font_scale); // Draws 1
                break;
            case 50 : 
                draw_character(x_coor,y,color,2,font_scale); // Draws 2
                break;
            case 51 : 
                draw_character(x_coor,y,color,3,font_scale); // Draws 3
                break;
            case 52 : 
                draw_character(x_coor,y,color,4,font_scale); // Draws 4
                break;
            case 53 : 
                draw_character(x_coor,y,color,5,font_scale); // Draws 5
                break;
            case 54 : 
                draw_character(x_coor,y,color,6,font_scale); // Draws 6
                break;
            case 55 : 
                draw_character(x_coor,y,color,7,font_scale); // Draws 7
                break;
            case 56 : 
                draw_character(x_coor,y,color,8,font_scale); // Draws 8
                break;
            case 57 : 
                draw_character(x_coor,y,color,9,font_scale); // Draws 9
                break;
            case 65 : 
                draw_character(x_coor,y,color,10,font_scale); // Draws A
                break;
            case 66 : 
                draw_character(x_coor,y,color,11,font_scale); // Draws B
                break;
            case 67 : 
                draw_character(x_coor,y,color,12,font_scale); // Draws C
                break;
            case 68 : 
                draw_character(x_coor,y,color,13,font_scale); // Draws D
                break;
            case 69 : 
                draw_character(x_coor,y,color,14,font_scale); // Draws E
                break;
            case 70 : 
                draw_character(x_coor,y,color,15,font_scale); // Draws F
                break;
            case 71 : 
                draw_character(x_coor,y,color,16,font_scale); // Draws G
                break;
            case 72 :
                draw_character(x_coor,y,color,17,font_scale); // Draws H
                break;
            case 73 :
                draw_character(x_coor,y,color,18,font_scale); // Draws I
                break;
            case 74 :
                draw_character(x_coor,y,color,19,font_scale); // Draws J
                break;
            case 75 :
                draw_character(x_coor,y,color,20,font_scale); // Draws K
                break;
            case 76 : 
                draw_character(x_coor,y,color,21,font_scale); // Draws L
                break;
            case 77 :
                draw_character(x_coor,y,color,22,font_scale); // Draws M
                break;
            case 78 :
                draw_character(x_coor,y,color,23,font_scale); // Draws N
                break;
            case 79 :
                draw_character(x_coor,y,color,24,font_scale); // Draws O
                break;
            case 80 :
                draw_character(x_coor,y,color,25,font_scale); // Draws P
                break;
            case 81 :
                draw_character(x_coor,y,color,26,font_scale); // Draws Q
                break;
            case 82 :
                draw_character(x_coor,y,color,27,font_scale); // Draws R
                break;
            case 83 :
                draw_character(x_coor,y,color,28,font_scale); // Draws S
                break;
            case 84 :
                draw_character(x_coor,y,color,29,font_scale); // Draws T
                break;
            case 85 :
                draw_character(x_coor,y,color,30,font_scale); // Draws U
                break;
            case 86 :
                draw_character(x_coor,y,color,31,font_scale); // Draws V
                break;
            case 87 :
                draw_character(x_coor,y,color,32,font_scale); // Draws W
                break;
            case 88 :
                draw_character(x_coor,y,color,33,font_scale); // Draws X
                break;
            case 89 :
                draw_character(x_coor,y,color,34,font_scale); // Draws Y
                break;
            case 90 :
                draw_character(x_coor,y,color,35,font_scale); // Draws Z
                break;
            case 46 :
                draw_character(x_coor,y,color,36,font_scale); // Draws .
                break;
            case 32 :
                draw_character(x_coor,y,color,37,font_scale); // Draws [space]
                break;
        }
        
        x_coor = x_coor+7*font_scale;
        if (x_coor>316)
        {
            x_coor = x;
            y = y-9;
        }
        
        string = string+1;
    }
}