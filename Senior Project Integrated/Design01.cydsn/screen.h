#if !defined(SCREEN_H)
#define SCREEN_H
    
    #define ILI9341_TFTWIDTH   240      ///< ILI9341 max TFT width
    #define ILI9341_TFTHEIGHT  320      ///< ILI9341 max TFT height

    #define ILI9341_NOP        0x00     ///< No-op register
    #define ILI9341_SWRESET    0x01     ///< Software reset register
    #define ILI9341_RDDID      0x04     ///< Read display identification information
    #define ILI9341_RDDST      0x09     ///< Read Display Status

    #define ILI9341_SLPIN      0x10     ///< Enter Sleep Mode
    #define ILI9341_SLPOUT     0x11     ///< Sleep Out
    #define ILI9341_PTLON      0x12     ///< Partial Mode ON
    #define ILI9341_NORON      0x13     ///< Normal Display Mode ON

    #define ILI9341_RDMODE     0x0A     ///< Read Display Power Mode
    #define ILI9341_RDMADCTL   0x0B     ///< Read Display MADCTL
    #define ILI9341_RDPIXFMT   0x0C     ///< Read Display Pixel Format
    #define ILI9341_RDIMGFMT   0x0D     ///< Read Display Image Format
    #define ILI9341_RDSELFDIAG 0x0F     ///< Read Display Self-Diagnostic Result

    #define ILI9341_INVOFF     0x20     ///< Display Inversion OFF
    #define ILI9341_INVON      0x21     ///< Display Inversion ON
    #define ILI9341_GAMMASET   0x26     ///< Gamma Set
    #define ILI9341_DISPOFF    0x28     ///< Display OFF
    #define ILI9341_DISPON     0x29     ///< Display ON

    #define ILI9341_CASET      0x2A     ///< Column Address Set
    #define ILI9341_PASET      0x2B     ///< Page Address Set
    #define ILI9341_RAMWR      0x2C     ///< Memory Write
    #define ILI9341_RAMRD      0x2E     ///< Memory Read

    #define ILI9341_PTLAR      0x30     ///< Partial Area
    #define ILI9341_MADCTL     0x36     ///< Memory Access Control
    #define ILI9341_VSCRSADD   0x37     ///< Vertical Scrolling Start Address
    #define ILI9341_PIXFMT     0x3A     ///< COLMOD: Pixel Format Set

    #define ILI9341_FRMCTR1    0xB1     ///< Frame Rate Control (In Normal Mode/Full Colors)
    #define ILI9341_FRMCTR2    0xB2     ///< Frame Rate Control (In Idle Mode/8 colors)
    #define ILI9341_FRMCTR3    0xB3     ///< Frame Rate control (In Partial Mode/Full Colors)
    #define ILI9341_INVCTR     0xB4     ///< Display Inversion Control
    #define ILI9341_DFUNCTR    0xB6     ///< Display Function Control

    #define ILI9341_PWCTR1     0xC0     ///< Power Control 1
    #define ILI9341_PWCTR2     0xC1     ///< Power Control 2
    #define ILI9341_PWCTR3     0xC2     ///< Power Control 3
    #define ILI9341_PWCTR4     0xC3     ///< Power Control 4
    #define ILI9341_PWCTR5     0xC4     ///< Power Control 5
    #define ILI9341_VMCTR1     0xC5     ///< VCOM Control 1
    #define ILI9341_VMCTR2     0xC7     ///< VCOM Control 2

    #define ILI9341_RDID1      0xDA     ///< Read ID 1
    #define ILI9341_RDID2      0xDB     ///< Read ID 2
    #define ILI9341_RDID3      0xDC     ///< Read ID 3
    #define ILI9341_RDID4      0xDD     ///< Read ID 4

    #define ILI9341_GMCTRP1    0xE0     ///< Positive Gamma Correction
    #define ILI9341_GMCTRN1    0xE1     ///< Negative Gamma Correction

    // Color definitions
    #define BLACK               0x0000  ///<   0,   0,   0
    #define NAVY                0x000F  ///<   0,   0, 123
    #define DARKGREEN           0x03E0  ///<   0, 125,   0
    #define DARKCYAN            0x03EF  ///<   0, 125, 123
    #define MAROON              0x7800  ///< 123,   0,   0
    #define PURPLE              0x780F  ///< 123,   0, 123
    #define OLIVE               0x7BE0  ///< 123, 125,   0
    #define LIGHTGREY           0xC618  ///< 198, 195, 198
    #define DARKGREY            0x7BEF  ///< 123, 125, 123
    #define BLUE                0x001F  ///<   0,   0, 255
    #define GREEN               0x07E0  ///<   0, 255,   0
    #define CYAN                0x07FF  ///<   0, 255, 255
    #define RED                 0xF800  ///< 255,   0,   0
    #define MAGENTA             0xF81F  ///< 255,   0, 255
    #define YELLOW              0xFFE0  ///< 255, 255,   0
    #define WHITE               0xFFFF  ///< 255, 255, 255
    #define ORANGE              0xFD20  ///< 255, 165,   0
    #define GREENYELLOW         0xAFE5  ///< 173, 255,  41
    #define PINK                0xFC18  ///< 255, 130, 198
    #define LIGHTBLUE           0x9E9F
    #define LIGHTRED            0xFCF3

    // Other definitions
    #define xstart              0
    #define ystart              0
    #define _width              240
    #define _height             320

    #define ILI9341_TFTWIDTH   240      ///< ILI9341 max TFT width
    #define ILI9341_TFTHEIGHT  320      ///< ILI9341 max TFT height
    
    #define Y_RES 230.0
    #define X_RES 320.0

    #define pgm_read_byte(addr) (*(const unsigned char *)(addr))

    #define MADCTL_MY  0x80  ///< Bottom to top
    #define MADCTL_MX  0x40  ///< Right to left
    #define MADCTL_MV  0x20  ///< Reverse Mode
    #define MADCTL_ML  0x10  ///< LCD refresh Bottom to top
    #define MADCTL_RGB 0x00  ///< Red-Green-Blue pixel order
    #define MADCTL_BGR 0x08  ///< Blue-Green-Red pixel order
    #define MADCTL_MH  0x04  ///< LCD refresh right to left

    #define NUMSAMPLES 2
    #define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
    
#endif /* (SCREEN_H) */