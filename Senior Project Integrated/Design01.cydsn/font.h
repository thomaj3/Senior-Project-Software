// Arrays holding font bitmaps
// 7 Lines starting from bottom and going up
// Read as  unint8_t font_0[] = 
//			{
//				# of pixels in line 0, 
//				(index of pixels from 0-4),
//				# of pixels in line 1...
//			}

#if !defined(FONT_H)
#define FONT_H

#include "project.h"

static const uint8_t font_0[] = 
{
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
    1,2,3
};

static const uint8_t font_1[] = 
{
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
    2
};

static const uint8_t font_2[] = 
{
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
    1,2,3
};

static const uint8_t font_3[] = 
{
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
    1,2,3
};

static const uint8_t font_4[] = 
{
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
    3,4
};

static const uint8_t font_5[] = 
{
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
    0,1,2,3,4
};

static const uint8_t font_6[] = 
{
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
    2,3
};

static const uint8_t font_7[] = 
{
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
    0,1,2,3,4
};

static const uint8_t font_8[] = 
{
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
    1,2,3
};

static const uint8_t font_9[] = 
{
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
    1,2,3
};

static const uint8_t font_period[] = 
{
    1,
    2,
    0,

    0,

    0,

    0,

    0,

    0
};

static const uint8_t font_a[] = 
{
    4,
    1,2,3,4,
    1,
    0,4,
    4,
    1,2,3,4,
    1,
    4,
    3,
    2,3,4,
    0,

    0
};

static const uint8_t font_b[] = 
{
    4,
    0,1,2,3,
    2,
    0,4,
    2,
    0,4,
    3,
    0,1,4,
    3,
    0,2,3,
    1,
    0,
    1,
    0
};

static const uint8_t font_c[] = 
{
    3,
    1,2,3,
    2,
    0,4,
    1,
    0,
    2,
    0,4,
    3,
    1,2,3,
    0,

    0
};

static const uint8_t font_d[] = 
{
    4,
    1,2,3,4,
    2,
    0,4,
    2,
    0,4,
    3,
    0,3,4,
    3,
    1,2,4,
    1,
    4,
    1,
    4
};

static const uint8_t font_e[] = 
{
    4,
    1,2,3,4,
    1,
    0,
    5,
    0,1,2,3,4,
    2,
    0,4,
    3,
    1,2,3,
    0,

    0
};

static const uint8_t font_f[] = 
{
    1,
    2,
    1,
    2,
    1,
    2,
    1,
    2,
    4,
    1,2,3,4,
    1,
    2,
    2,
    3,4
};


// Needs changes to go under the line
static const uint8_t font_g[] = 
{
    4,
    0,1,2,3,
    1,
    4,
    4,
    1,2,3,4,
    2,
    0,4,
    2,
    0,4,
    4,
    1,2,3,4,
    0
};

static const uint8_t font_h[] = 
{
    2,
    0,4,
    2,
    0,4,
    2,
    0,4,
    3,
    0,1,4,
    3,
    0,2,3,
    1,
    0,
    1,
    0
};

static const uint8_t font_i[] = 
{
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
    0,

    1,
    2,
};

// Needs changes to go under the line
static const uint8_t font_j[] = 
{
	
};


// Capital Letters
static const uint8_t font_A[] = 
{
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
    5,
    0,1,2,3,4,
    2,
    0,4,
    3,
    1,2,3
};

static const uint8_t font_B[] = 
{
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
    0,1,2,3
};

static const uint8_t font_C[] = 
{
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
    1,2,3
};

static const uint8_t font_D[] = 
{
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
    0,1,2,3
};

// Different from reference font
static const uint8_t font_E[] = 
{
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
    0,1,2,3,4
};

static const uint8_t font_F[] = 
{
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
    0,1,2,3,4
};

static const uint8_t font_G[] = 
{
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
    1,2,3,4
};

#endif /* (FONT_H) */