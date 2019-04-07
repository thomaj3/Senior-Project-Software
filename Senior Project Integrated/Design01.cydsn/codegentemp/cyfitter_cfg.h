/*******************************************************************************
* File Name: cyfitter_cfg.h
* 
* PSoC Creator  4.2
*
* Description:
* This file provides basic startup and mux configuration settings
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#ifndef CYFITTER_CFG_H
#define CYFITTER_CFG_H

#include "cytypes.h"

extern void cyfitter_cfg(void);

/* Analog Set/Unset methods */
extern void SetAnalogRoutingPumps(uint8 enabled);
extern void AMux_1_Set(uint8 channel);
extern void AMux_1_Unset(uint8 channel);
/* AMux_1__addrTable is an implementation detail of the AMux.
   Code that depends on it may be incompatible with other versions
   of PSoC Creator. */
extern uint8 CYXDATA * const CYCODE AMux_1__addrTable[2];
/* AMux_1__maskTable is an implementation detail of the AMux.
   Code that depends on it may be incompatible with other versions
   of PSoC Creator. */
extern const uint8 CYCODE AMux_1__maskTable[2];
extern void AMux_2_Set(uint8 channel);
extern void AMux_2_Unset(uint8 channel);
/* AMux_2__addrTable is an implementation detail of the AMux.
   Code that depends on it may be incompatible with other versions
   of PSoC Creator. */
extern uint8 CYXDATA * const CYCODE AMux_2__addrTable[2];
/* AMux_2__maskTable is an implementation detail of the AMux.
   Code that depends on it may be incompatible with other versions
   of PSoC Creator. */
extern const uint8 CYCODE AMux_2__maskTable[2];
extern void AMux_3_Set(uint8 channel);
extern void AMux_3_Unset(uint8 channel);
/* AMux_3__addrTable is an implementation detail of the AMux.
   Code that depends on it may be incompatible with other versions
   of PSoC Creator. */
extern uint8 CYXDATA * const CYCODE AMux_3__addrTable[4];
/* AMux_3__maskTable is an implementation detail of the AMux.
   Code that depends on it may be incompatible with other versions
   of PSoC Creator. */
extern const uint8 CYCODE AMux_3__maskTable[4];


#endif /* CYFITTER_CFG_H */

/*[]*/
