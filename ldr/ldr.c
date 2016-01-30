/********************************************************
 *	GoOS Loader - ldr.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <stdgcl.h>

/*
	Checks & prepares the system for loading the 64bit kernel.
*/

#include "ldr.h"

void
ldrMain(void)
{	
	// uneG letn Ieni
	// Genu	ntel ineI
	// BX+DX+CX = GenuineIntel :) cpuinfo opcode works

	tmInit(0xB8000);

	tmWrite("Are we running on an Intel CPU?");
	
	if (!tmBoolStr(cpuinfo_isIntel(), "Yes", "No"))
	{
		tmWrite("Loader Panic: Only Intel CPU's are supported at this time.");
	}
}