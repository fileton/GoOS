/********************************************************
 *	GoOS Loader - ldr.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include "ldr.h"
#include "textmode.h"
#include "multiboot.h" // thirdparty
#include <stdlib.h>
#include <bda.h>
#include <cpuid.h>

void
ldrMain(void)
{	
	// uneG letn Ieni
	// Genu	ntel ineI
	// BX+DX+CX = GenuineIntel :) cpuinfo opcode works

	tmInit(0xB8000);

	tmWriteHex(bda_vga_ioport);
	tmWriteChr(' ');

	tmCursor_t curpos = tmGetCursor();

	tmWriteUInt(curpos.column);
	tmWriteChr(':');
	tmWriteUInt(curpos.row);
	tmWrite(" -> ");

	uint a = 0;
	uint b;
	uint c;
	uint d;

	cpuinfo_opcode(&a, &b, &c, &d);

	tmWriteHex(a);
	tmWriteChr(' ');
	tmWriteHex(b);

	tmWriteChr(' ');
	tmWriteHex(c);

	tmWriteChr(' ');
	tmWriteHex(d);
}