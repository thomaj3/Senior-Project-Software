/*******************************************************************************
* File Name: Mux_1.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_Mux_1_H)
#define CY_AMUX_Mux_1_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void Mux_1_Start(void) ;
#define Mux_1_Init() Mux_1_Start()
void Mux_1_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void Mux_1_Stop(void); */
/* void Mux_1_Select(uint8 channel); */
/* void Mux_1_Connect(uint8 channel); */
/* void Mux_1_Disconnect(uint8 channel); */
/* void Mux_1_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define Mux_1_CHANNELS  2u
#define Mux_1_MUXTYPE   1
#define Mux_1_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define Mux_1_NULL_CHANNEL 0xFFu
#define Mux_1_MUX_SINGLE   1
#define Mux_1_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if Mux_1_MUXTYPE == Mux_1_MUX_SINGLE
# if !Mux_1_ATMOSTONE
#  define Mux_1_Connect(channel) Mux_1_Set(channel)
# endif
# define Mux_1_Disconnect(channel) Mux_1_Unset(channel)
#else
# if !Mux_1_ATMOSTONE
void Mux_1_Connect(uint8 channel) ;
# endif
void Mux_1_Disconnect(uint8 channel) ;
#endif

#if Mux_1_ATMOSTONE
# define Mux_1_Stop() Mux_1_DisconnectAll()
# define Mux_1_Select(channel) Mux_1_FastSelect(channel)
void Mux_1_DisconnectAll(void) ;
#else
# define Mux_1_Stop() Mux_1_Start()
void Mux_1_Select(uint8 channel) ;
# define Mux_1_DisconnectAll() Mux_1_Start()
#endif

#endif /* CY_AMUX_Mux_1_H */


/* [] END OF FILE */
