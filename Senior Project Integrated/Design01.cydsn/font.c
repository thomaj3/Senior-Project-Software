// Steven Andresen
// Senior Project Spring 2019

#include "project.h"
#include "font.h"
#include "screen.h"

// How to read
//  // Number
//  # of array indecies to next number

//  # of pixels in line 0, 
//	(index of pixels from 0-4),
//	# of pixels in line 1...

//  //Number...

static const uint8_t font[] = 
{
    // Font Height
    7,
    
    // 0
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
    
    // 1
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
    
    // 2
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
    
    // 3
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
    
    // 4
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
    
    // 5
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
    
    // 6
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
    
    // 7
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
    
    // 8
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
    
    // 9
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
    
    // A
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
    
    // B
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
    
    // C
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
    
    // D
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
    
    // E
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
    
    // F
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
    
    // G
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
    
    // H
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
    
    // I
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
    
    // J
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
    
    // K
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
    
    // L
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
    
    // M
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
    
    // N
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
    
    // O
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
    
    // P
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
    
    // Q
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
    
    // R
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
    
    // S
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
    
    // T
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
    
    // U
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
    
    // V
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
    
    // W
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
    
    // X
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
    
    // Y
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
    
    // Z
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
    
    // .
    8,
    
    1,
    2,
    0,

    0,

    0,

    0,

    0,

    0,
    
    // [space]
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

void draw_string(int16_t x, int16_t y, uint16_t color, char *string[])
{
    int16_t x_coor = x;
    
    for(int i=0; i<(sizeof(*string)/sizeof(*string[0])-1); i++)
    {
        switch(*string[i])
        {
            case 48 : 
                draw_character(x_coor,y,color,0); // Draws 0
            case 49 : 
                draw_character(x_coor,y,color,1); // Draws 1
            case 50 : 
                draw_character(x_coor,y,color,2); // Draws 2
            case 51 : 
                draw_character(x_coor,y,color,3); // Draws 3
            case 52 : 
                draw_character(x_coor,y,color,4); // Draws 4
            case 53 : 
                draw_character(x_coor,y,color,5); // Draws 5
            case 54 : 
                draw_character(x_coor,y,color,6); // Draws 6
            case 55 : 
                draw_character(x_coor,y,color,7); // Draws 7
            case 56 : 
                draw_character(x_coor,y,color,8); // Draws 8
            case 57 : 
                draw_character(x_coor,y,color,9); // Draws 9
            case 65 : 
                draw_character(x_coor,y,color,10); // Draws A
            case 66 : 
                draw_character(x_coor,y,color,11); // Draws B
            case 67 : 
                draw_character(x_coor,y,color,12); // Draws C
            case 68 : 
                draw_character(x_coor,y,color,13); // Draws D
            case 69 : 
                draw_character(x_coor,y,color,14); // Draws E
            case 70 : 
                draw_character(x_coor,y,color,15); // Draws F
            case 71 : 
                draw_character(x_coor,y,color,16); // Draws G    
        }
        
        x_coor = x_coor+7;
        if (x_coor>319)
        {
            x_coor = x;
            y = y+9;
        }
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
    draw_character(x+x_offset+7,y,color,10);
    draw_character(x+x_offset+14,y,color,tenths);
    draw_character(x+x_offset+21,y,color,hundredths);
    draw_character(x+x_offset+28,y,color,thousandths);
}