// Steven Andresen
// Senior Project Fall 2018

#include "project.h"
#include "screen.h"
#include "strings.h"


// Initialization command/data
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
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
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

// Fills screen a single color
void fill_screen(uint16_t color) 
{
  fillRect(0, 0,  _width, _height, color);
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
