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
    0,4
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