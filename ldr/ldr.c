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

void
ldrMain(void)
{	
	// Init textmode
	tmInit(0xB8000);

	// Is it a 64bit cpu from Intel or AMD?
	tmWrite("Is your CPU supported?");
	BochsBreak();
	gclPanicBoolStr(cpuid_cpu_supported(), "Yes", "No", "Sorry, only 64bit CPU's from Intel or AMD are supported.");
}