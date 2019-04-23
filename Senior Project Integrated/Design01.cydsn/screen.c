// Steven Andresen
// Senior Project Fall 2018-2019

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

//Initialization command/data
static const uint8_t initcmd[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,
  0xED, 4, 0x64, 0x03, 0x12, 0x81,
  0xE8, 3, 0x85, 0x00, 0x78,
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
  0xF7, 1, 0x20,
  0xEA, 2, 0x00, 0x00,
  ILI9341_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
  ILI9341_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
  ILI9341_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
  ILI9341_VMCTR2  , 1, 0x86,             // VCM control2
  ILI9341_MADCTL  , 1, 0x48,             // Memory Access Control
  ILI9341_VSCRSADD, 1, 0x00,             // Vertical scroll zero
  ILI9341_PIXFMT  , 1, 0x55,
  ILI9341_FRMCTR1 , 2, 0x00, 0x18,
  ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
  0xF2, 1, 0x00,                         // 3Gamma Function Disable
  ILI9341_GAMMASET , 1, 0x01,             // Gamma curve selected
  ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
  ILI9341_SLPOUT  , 0x80,                // Exit Sleep
  ILI9341_DISPON  , 0x80,                // Display on
  0x00                                   // End of list
};

// Write command over SPI buss
void writecommand(uint8_t command)
{
    // Set D_C to low for command
    D_C_Write(0);
    SPIM_WriteTxData(command);
    while(SS_Read() != 0){}
    while(SS_Read() != 1){}
}

// Writes data over SPI bus
void writedata(uint8_t data)
{
    // Set D_C to high for data
    D_C_Write(1);
    SPIM_WriteTxData(data);
    while(SS_Read() != 0){}
    while(SS_Read() != 1){}
}

// Sets addresses in memory to write to
void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    uint32_t xa = ((uint32_t)x << 16) | (x+w-1);
    uint32_t ya = ((uint32_t)y << 16) | (y+h-1);
    
    // Column address set
    writecommand(ILI9341_CASET);
    
    // Splits 'x' addresses 32-bit into 4 bytes
    D_C_Write(1);
    SS_Write(0);
    SPIM_WriteTxData(xa >> 24);
    while(SS_Read() != 1){}
    SPIM_WriteTxData(xa >> 16);
    while(SS_Read() != 1){}
    SPIM_WriteTxData(xa >> 8);
    while(SS_Read() != 1){}
    SPIM_WriteTxData(xa >> 0);
    while(SS_Read() != 1){}
    SS_Write(1);
    
    // Page address set
    writecommand(ILI9341_PASET);
    
    // Splits 'y' addresses 32-bit into 4 bytes
    D_C_Write(1);
    SS_Write(0);
    SPIM_WriteTxData(ya >> 24);
    while(SS_Read() != 1){}
    SPIM_WriteTxData(ya >> 16);
    while(SS_Read() != 1){}
    SPIM_WriteTxData(ya >> 8);
    while(SS_Read() != 1){}
    SPIM_WriteTxData(ya >> 0);
    while(SS_Read() != 1){}
    SS_Write(1);
    
    writecommand(ILI9341_RAMWR);
}

// Fills in a rectangle of color on the screen
void draw_rect(int16_t x, int16_t y, int16_t w, int16_t h,
  uint16_t color) 
{

    // rudimentary clipping (drawChar w/big text requires this)
    if((x >= _width) || (y >= _height)) return;
    if((x + w - 1) >= _width)  w = _width  - x;
    if((y + h - 1) >= _height) h = _height - y;

    // Sets addresses in memory to write to
    setAddrWindow(x, y, w, h);

    // Splits color into two bytes
    uint8_t hi = color >> 8, lo = color;
    
    #if defined (SPI_HAS_TRANSACTION)
      if (hwSPI)      SPI.beginTransaction(mySPISettings);
    #endif

    D_C_Write(1);
    SS_Write(0);
    // Writes color to addresses
    for(y=h; y>0; y--) 
    {
        for(x=w; x>0; x--) 
        {
            SPIM_WriteTxData(hi);
            while(SS_Read() != 1){}
            SPIM_WriteTxData(lo);
            while(SS_Read() != 1){}
        }
    }
    SS_Write(1);

    #if defined (SPI_HAS_TRANSACTION)
      if (hwSPI)      SPI.endTransaction();
    #endif
}



void fill_rect(int16_t x, int16_t y, int16_t w, int16_t h,
  uint16_t color)
{
    draw_rect((240-y-h), (320-x-w), h, w, color);
}

// Fills screen a single color
void fill_screen(uint16_t color) 
{
  fill_rect(0, 0,  _height, _width, color);
}

// Sends commands and data to configure screen for display
void StartScreen() 
{
    uint8_t        cmd, x, numArgs;
    const uint8_t *addr = initcmd;
    
    // Iterates through cmd/data array
    while((cmd = pgm_read_byte(addr++)) > 0) 
    {
        writecommand(cmd);
        x       = pgm_read_byte(addr++);
        numArgs = x & 0x7F;
        while(numArgs--)
        {
            writedata(pgm_read_byte(addr++));
        }
        if(x & 0x80) CyDelay(120);
    }
}

void change_pixel(int16_t x, int16_t y, uint16_t color)
{
    //Make sure pixel is on screen
    if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;

    //Sets memory address to write to
    setAddrWindow(x,y,1,1);

    #if defined (SPI_HAS_TRANSACTION)
        if (hwSPI)     SPI.beginTransaction(mySPISettings);
    #endif

    //Writes 2-byte color to memory
    D_C_Write(1);
    SS_Write(0);
    SPIM_WriteTxData(color >> 8);
    while(SS_Read() != 1){}
    SPIM_WriteTxData(color);
    while(SS_Read() != 1){}
    SS_Write(1);

    #if defined (SPI_HAS_TRANSACTION)
        if (hwSPI)     SPI.endTransaction();
    #endif
}

// Changes pixel color at specified coordinates
void draw_pixel(int16_t x, int16_t y, uint16_t color) 
{    
    change_pixel(239-y, 319-x, color);
//    change_pixel(y, x, color);
}

// Draws 1 pixel lines on the screen from one coordinate to another
void write_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
        uint16_t color) 
{
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) 
    {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }
    if (x0 > x1)
    {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) 
    {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) 
    {
        if (steep) 
        {
            draw_pixel(y0, x0, color);
        } else 
        {
            draw_pixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) 
        {
            y0 += ystep;
            err += dx;
        }
    }
}
    
// Draws horizontal line
void drawFastHLine(int16_t x, int16_t y,
int16_t w, uint16_t color)
{
    // Calls write_line
    write_line(x, y, x+w-1, y, color);
}

// Draws vertical line
void drawFastVLine(int16_t x, int16_t y,
        int16_t h, uint16_t color) 
{
    // Calls write_line
    write_line(x, y, x, y+h-1, color);
}

// Calls proper way to draw a line
void draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
        uint16_t color)
{
    // Checks is line is vertical
    if(x0 == x1)
    {
        if(y0 > y1) _swap_int16_t(y0, y1);
        drawFastVLine(x0, y0, y1 - y0 + 1, color);
    } 
    // Checks if line is horizontal
    else if(y0 == y1)
    {
        if(x0 > x1) _swap_int16_t(x0, x1);
        drawFastHLine(x0, y0, x1 - x0 + 1, color);
    } 
    else 
    {
        write_line(x0, y0, x1, y1, color);
    }
}

void fill_circle_helper(int16_t x0, int16_t y0, int16_t r,
  uint8_t corners, int16_t delta, uint16_t color) {

    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
    int16_t px    = x;
    int16_t py    = y;

    delta++; // Avoid some +1's in the loop

    while(x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        // These checks avoid double-drawing certain lines, important
        // for the SSD1306 library which has an INVERT drawing mode.
        if(x < (y + 1)) {
            if(corners & 1) drawFastVLine(x0+x, y0-y, 2*y+delta, color);
            if(corners & 2) drawFastVLine(x0-x, y0-y, 2*y+delta, color);
        }
        if(y != py) {
            if(corners & 1) drawFastVLine(x0+py, y0-px, 2*px+delta, color);
            if(corners & 2) drawFastVLine(x0-py, y0-px, 2*px+delta, color);
            py = y;
        }
        px = x;
    }
}

void fill_circle(int16_t x0, int16_t y0, int16_t r,
        uint16_t color) {
    //startWrite();
    drawFastVLine(x0, y0-r, 2*r+1, color);
    fill_circle_helper(x0, y0, r, 3, 0, color);
    //endWrite();
}

void draw_button(int16_t x, int16_t y, int16_t w, int16_t h, 
        uint16_t button_color, uint16_t text_color, char string[])
{
    //fills in the rectangle on the screen for the button
    fill_rect(x,y,w,h,button_color);
    
    //defines needed variables
    int rect_center_x = x+(w/2);
    int rect_center_y = y+(h/2);
    int string_length = 0;
    
    //gets the length of the string
    while(*string != 0)
    {
        string_length++;
        string++;
    }
    
    char the_string[string_length+1];
    
    string = string-string_length; //resets string pointer
    
    //recreates the string as a character array
    for(int i = 0;i<string_length;i++)
    {
        the_string[i] = *string;
        string++;
    }
    
    //adds null character to end of string
    the_string[string_length] = 0;
    
    //if the string can fit in the button in one line
    if(string_length*7<w)
    {
        //gets starting x-coord. of string
        int pixel_start = rect_center_x - string_length*7/2 + 3;
        
        //prints string to center of button rectangle
        draw_string(pixel_start,rect_center_y-1,text_color,the_string,1);
    }
    //if the string takes more than one line to fit in the button
    //NOTE! right now this only works for 2 lines. It should be able
    //to be addapted for multiple lines easily
    else if(string_length*7>w)
    {
        int button_character_width = w/7-1;
        
        while(the_string[button_character_width] != 32)
        {
            button_character_width--;
        }
        
        char new_string_1[button_character_width+1];
        char new_string_2[string_length-button_character_width+1];
        
        for(int i = 0; i<button_character_width; i++)
        {
            new_string_1[i] = the_string[i];
        }
        for(int i = 0; i<string_length-button_character_width; i++)
        {
            new_string_2[i] = the_string[button_character_width+i+1];
        }
        
        new_string_1[button_character_width] = 0;
        new_string_2[string_length-button_character_width] = 0;
        
        int new_string_1_length = sizeof(new_string_1)/sizeof(new_string_1[0]);
        int new_string_2_length = sizeof(new_string_2)/sizeof(new_string_2[0])-1;
        
        //gets starting x-coord. of string
        int pixel_start_1 = rect_center_x - new_string_1_length*7/2 + 5;
        int pixel_start_2 = rect_center_x - new_string_2_length*7/2 + 4;
        
        //prints string to center of button rectangle
        draw_string(pixel_start_1,rect_center_y+3,text_color,new_string_1,1);
        draw_string(pixel_start_2,rect_center_y-5,text_color,new_string_2,1);
    }
}

void draw_coordinates(int y_max, unsigned int device_selection)
{
    fill_screen(BLACK);
    
    int y_max_pixel = (int) ((0.8)*240);
    int five_mA_pixel = (int) (y_max_pixel*5.0/y_max);
    int y_label;
    int x_label;
    char string_throwaway_y[10];
    char string_throwaway_x[4]; //= NULL;
    //string_print = malloc(sizeof(**string_print)*3);
    int x_max_step;
    int i;
    int k;
    draw_line(30,10,220,10,WHITE); //draw x axis line
    draw_line(30,10,30,y_max_pixel+9,WHITE);//draw y axis line
    
    if(device_selection < 2)
    {
        x_max_step = 189/9;
    }
    else
    {
        x_max_step = 189/15;
    }
    
    if((device_selection%2) == 0)
    {
        draw_string(230,4,WHITE,"VDS V",1);
        draw_string(3,y_max_pixel + 25,WHITE,"ID MIL A",1);
    }
    else
    {
        draw_string(230,4,WHITE,"VCE V",1);
        draw_string(3,y_max_pixel+ 25,WHITE,"IC MIL A",1);
    }
    
    for(i=1; 5*i <= y_max ;i++)
    {
        y_label =  5 * i;
        sprintf(string_throwaway_y,"%d", y_label);
        
        if(draw_grid == 1)
        {
            draw_line(30,i*five_mA_pixel+10,220,i*five_mA_pixel+10,WHITE);//draw y major 
        }
        draw_string(3,i*five_mA_pixel+10,WHITE,string_throwaway_y,1);//draw y major label
        
    }
    
    for(i = 1; i <= 189/x_max_step; i++)
    {
        sprintf(string_throwaway_x,"%i", i);
        if(draw_grid == 1)
        {
            draw_line(i*x_max_step+30,10,i*x_max_step+30,y_max_pixel+10,WHITE);//draw x major
        }
        draw_string(i*x_max_step+30,4,WHITE,string_throwaway_x,1);//draw x major label
    }
    
    //DO NOT TOUCH! without having the string be separate from
    //the draw_button function, it will write "STOPH"
    //might be fixed now, added null char to end of recreated string in draw_button
    //don't want to tempt fate by changing this
    char temp[] = "STOP";
    
    draw_button(130,209,60,30,RED,BLACK,temp);
        
    screen_state = PLOT_SCREEN;   //sets screen state to graph screen
}

void draw_choose_screen()
{
    screen_state = DEVICE_SELECTION_SCREEN;
    
    //fills in background color
    fill_rect(0,0,160,240,BLUE);
    fill_rect(160,0,160,240,RED);
    
    //creates lines to separate buttons
    fill_rect(159,0,2,240,BLACK);
    fill_rect(0,119,320,2,BLACK);
    
    //center background colors
    fill_rect(33,109,252,22,BLACK);
    
    //draws buttons
    draw_button(35,111,248,18,WHITE,BLACK,"CHOOSE A SEMICONDUCTOR TYPE");
    draw_button(10,10,139,99,LIGHTBLUE,BLACK,"N TYPE FET");
    draw_button(10,131,139,99,LIGHTBLUE,BLACK,"NPN BJT");
    draw_button(171,10,139,99,LIGHTRED,BLACK,"P TYPE FET");
    draw_button(171,131,139,99,LIGHTRED,BLACK,"PNP BJT");
}

void draw_options_screen()
{
    screen_state = OPTIONS_SCREEN;
    
    //need temp variables for strings otherwise it reads
    //into the next string upon returning from an option screen
    //might be fixed now, added null char to end of recreated string in draw_button
    //don't want to tempt fate by changing this
    char temp1[] = "NUMBER OF AVERAGES";
    char temp2[] = "SD CARD OPTIONS";
    char temp3[] = "MORE OPTIONS";
    char temp4[] = "NUMBER OF CURVES"; //PLOTTING GRID OPTIONS
    char temp5[] = "RETURN";
    char temp6[] = "RUN TEST";
    
    //draws buttons
    draw_button(0,0,119,119,LIGHTBLUE,BLACK,temp1);
    draw_button(0,121,119,119,LIGHTRED,BLACK,temp2);
    draw_button(121,0,119,119,LIGHTRED,BLACK,temp3);
    draw_button(121,121,119,119,LIGHTBLUE,BLACK,temp4);
    
    draw_button(241,0,79,119,WHITE,BLACK,temp5);
    draw_button(241,121,79,119,WHITE,BLACK,temp6);
    
    //creates lines to separate buttons
    fill_rect(119,0,2,240,BLACK);
    fill_rect(0,119,320,2,BLACK);
    fill_rect(239,0,2,240,BLACK);
}

void draw_more_options_screen()
{
    screen_state = OPTIONS_SCREEN_2;
    
    //need temp variables for strings otherwise it reads
    //into the next string upon returning from an option screen
    //might be fixed now, added null char to end of recreated string in draw_button
    //don't want to tempt fate by changing this
    //char temp1[] = "NUMBER OF AVERAGES";
    char temp2[] = "PLOTTING GRID OPTIONS";
    //char temp3[] = "MORE OPTIONS";
    char temp4[] = "COOLDOWN TIME OPTIONS";
    char temp5[] = "RETURN";
    char temp6[] = "RUN TEST";
    
    //draws buttons
    //draw_button(0,0,119,119,LIGHTBLUE,BLACK,temp1);
    draw_button(0,121,119,119,LIGHTRED,BLACK,temp2);
    //draw_button(121,0,119,119,LIGHTRED,BLACK,temp3);
    draw_button(121,121,119,119,LIGHTBLUE,BLACK,temp4);
    fill_rect(0,0,241,119,WHITE);
    
    draw_button(241,0,79,119,WHITE,BLACK,temp5);
    draw_button(241,121,79,119,WHITE,BLACK,temp6);
    
    //creates lines to separate buttons
    fill_rect(119,119,2,120,BLACK);
    fill_rect(0,119,320,2,BLACK);
    fill_rect(239,0,2,240,BLACK);
}

void draw_options_averages_screen()
{
    screen_state = OPTION_AVERAGES_SCREEN;
    
    fill_screen(BLACK);
    
    draw_button(0,219,239,20,WHITE,BLACK,"NUMBER OF AVERAGES TO TAKE");
    
    draw_button(80,150,70,50,WHITE,BLACK,"PLUS 1");
    draw_button(80,80,70,50,WHITE,BLACK,"PLUS 10");
    draw_button(80,10,70,50,WHITE,BLACK,"PLUS 100");
    
    draw_button(160,150,70,50,WHITE,BLACK,"MINUS 1");
    draw_button(160,80,70,50,WHITE,BLACK,"MINUS 10");
    draw_button(160,10,70,50,WHITE,BLACK,"MINUS 100");
    
    char avg_num[4];
    itoa(num_avg, avg_num, 10);
    
    draw_string(20,105,WHITE,avg_num,2);
    
    //Return button with boundary
    draw_button(241,0,79,240,WHITE,BLACK,"RETURN");
    fill_rect(239,0,2,240,BLACK);
}

void draw_options_sd_screen()
{
    screen_state = OPTION_SD_SCREEN;
    
    fill_screen(BLACK);
    
    draw_button(0,219,239,20,WHITE,BLACK,"SD CARD OPTIONS");
    char temp[] = "WRITE RESULTS TO SD CARD";
    draw_button(0,170,239,10,WHITE,BLACK,temp);
    
    if(write_sd == 1)
    {
        draw_button(30,100,80,50,LIGHTBLUE,BLACK,"YES");
        draw_button(130,100,80,50,WHITE,BLACK,"NO");
    }
    else if(write_sd == 0)
    {
        draw_button(30,100,80,50,WHITE,BLACK,"YES");
        draw_button(130,100,80,50,LIGHTBLUE,BLACK,"NO");
    }
    else
    {
        draw_button(80,100,80,50,WHITE,BLACK,"YES");
        draw_button(130,100,80,50,WHITE,BLACK,"NO");
    }
    
    //Return button with boundary
    draw_button(241,0,79,240,WHITE,BLACK,"RETURN");
    fill_rect(239,0,2,240,BLACK);
}

void draw_options_curves_screen()
{
    screen_state = OPTION_CURVES_SCREEN;
    
    fill_screen(BLACK);
    
    draw_button(0,219,239,20,WHITE,BLACK,"NUMBER OF CURVES TO DRAW");
    
    draw_button(130,30,70,70,WHITE,BLACK,"DECREASE");
    draw_button(130,120,70,70,WHITE,BLACK,"INCREASE");
    
    char num_curve[2];
    itoa(curve_nums, num_curve, 10);
    
    draw_string(50,105,WHITE,num_curve,3);
    
    //Return button with boundary
    draw_button(241,0,79,240,WHITE,BLACK,"RETURN");
    fill_rect(239,0,2,240,BLACK);
}

void draw_options_grid_screen()
{
    screen_state = OPTION_GRID_SCREEN;
    
    fill_screen(BLACK);
    
    draw_button(0,219,239,20,WHITE,BLACK,"PLOTTING GRID OPTIONS SCREEN");
    
    char temp[] = "ENABLE GRID OVERLAY FOR PLOT SCREEN";
    draw_button(0,170,239,20,WHITE,BLACK,temp);
    
    if(draw_grid == 1)
    {
        draw_button(30,100,80,50,LIGHTBLUE,BLACK,"YES");
        draw_button(130,100,80,50,WHITE,BLACK,"NO");
    }
    else if(draw_grid == 0)
    {
        draw_button(30,100,80,50,WHITE,BLACK,"YES");
        draw_button(130,100,80,50,LIGHTBLUE,BLACK,"NO");
    }
    else
    {
        draw_button(80,100,80,50,WHITE,BLACK,"YES");
        draw_button(130,100,80,50,WHITE,BLACK,"NO");
    }
    
    //Return button with boundary
    draw_button(241,0,79,240,WHITE,BLACK,"RETURN");
    fill_rect(239,0,2,240,BLACK);
}

void draw_options_cooldown_screen()
{
    screen_state = OPTION_COOLDOWN_SCREEN;
    
    fill_screen(BLACK);
    
    draw_button(0,219,239,20,WHITE,BLACK,"RATIO OF TIME FOR DUT TO COOL AGAINST RUNNING TEST");
    
    draw_button(40,15,70,50,WHITE,BLACK,"5");
    draw_button(130,15,70,50,WHITE,BLACK,"10");
    draw_button(40,85,70,50,WHITE,BLACK,"1");
    draw_button(130,85,70,50,WHITE,BLACK,"2");
    draw_button(85,155,70,50,WHITE,BLACK,"NO COOLDOWN");
    
    switch(cooldown_time)
    {
        case 0 :
            draw_button(85,155,70,50,LIGHTBLUE,BLACK,"NO COOLDOWN");
            break;
        case 1 :
            draw_button(40,85,70,50,LIGHTBLUE,BLACK,"1");
            break;
        case 2 :
            draw_button(130,85,70,50,LIGHTBLUE,BLACK,"2");
            break;
        case 5 :
            draw_button(40,15,70,50,LIGHTBLUE,BLACK,"5");
            break;
        case 10 :
            draw_button(130,15,70,50,LIGHTBLUE,BLACK,"10");
            break;
    }
    
    //Return button with boundary
    draw_button(241,0,79,240,WHITE,BLACK,"RETURN");
    fill_rect(239,0,2,240,BLACK);
}

//screen used for debugging. Feel free to change as needed, keep return button
//should be changed into easter egg screen when finished
void draw_debug_screen(uint16_t x, uint16_t y)
{
    fill_screen(WHITE);
    
    screen_state = DEBUG_SCREEN;
    
    //return button
    //DO NOT TOUCH!!
    //draw_button(0,0,50,30,BLACK,WHITE,"RETURN");
    
//    char x_touch[10];
//    char y_touch[10];
//
//    itoa(x, x_touch, 10);
//    itoa(y, y_touch, 10);
//    
//    draw_string(100,110,WHITE,x_touch,1);
//    draw_string(100,100,WHITE,y_touch,1);
//    
//    draw_string(100,200,WHITE,"TOUCH COORDINATES",1);
//    
//    draw_string(50,150,WHITE,"TEST",6);
//    
//    draw_button(150,40,119,70,WHITE,BLACK,"SETTLING TIME OPTIONS");
    draw_string(5,230,BLACK,"MAKING",1);
    draw_string(5,222,BLACK,"DOUGH",1);
    fill_circle(159,119,110,PIZZATIME_1);
    if(screen_state != DEBUG_SCREEN)
    {
        return;
    }
    fill_rect(0,220,80,19,WHITE);
    draw_string(5,230,BLACK,"APPLYING",1);
    draw_string(5,222,BLACK,"SAUCE",1);
    fill_circle(159,119,95,PIZZATIME_2);
    if(screen_state != DEBUG_SCREEN)
    {
        return;
    }
    fill_rect(0,220,80,19,WHITE);
    draw_string(5,230,BLACK,"YUMMY",1);
    draw_string(5,222,BLACK,"CHEESE",1);
    fill_circle(159,119,90,PIZZATIME_3);
    if(screen_state != DEBUG_SCREEN)
    {
        return;
    }
    fill_rect(0,220,80,19,WHITE);
    draw_string(5,230,BLACK,"ADDING",1);
    draw_string(5,222,BLACK,"TOPPINGS",1);   
    fill_circle(130,84,10,PIZZATIME_2);
    if(screen_state != DEBUG_SCREEN)
    {
        return;
    }
    fill_circle(115,148,10,PIZZATIME_2);
    fill_circle(184,132,10,PIZZATIME_2);
    fill_circle(92,113,10,PIZZATIME_2);
    fill_circle(205,98,10,PIZZATIME_2);
    fill_circle(148,116,10,PIZZATIME_2);
    fill_circle(184,68,10,PIZZATIME_2);
    fill_circle(153,54,10,PIZZATIME_2);
    fill_circle(174,189,10,PIZZATIME_2);
    fill_circle(140,168,10,PIZZATIME_2);
    fill_circle(208,154,10,PIZZATIME_2);
    fill_rect(0,220,80,19,WHITE);
    
    int time = 1000;
    int text_color[] = {BLUE, GREEN, RED, ORANGE, BLACK, CYAN, PINK, LIGHTGREY, OLIVE, GREENYELLOW};
    srand(rand_num_1*rand_num_2);
    
    for(;;)
    {
        int x1 = rand() % 231;
        int y1 = rand() % 236;
        int size = rand() % 4;
        int rand_color = rand() % 10;
        draw_string(x1,y1,text_color[rand_color],"PIZZA TIME",size);
        
        CyDelay(time);
        time = time-10;
        if(time < 1)
        {
            time = 1;
        }
        if(screen_state != DEBUG_SCREEN)
        {
            break;
        }
    }
}