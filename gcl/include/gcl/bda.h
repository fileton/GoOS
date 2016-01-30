/********************************************************
 *	GoOS C Library - bda.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include "stdgcl.h"
#include "stdint.h"


#define bda_vga_ioport (*(volatile uint16_t *)(0x463 & 0xFFFF))