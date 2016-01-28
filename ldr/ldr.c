/********************************************************
 * 				GoOS Loader - ldr.c
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

void
ldrMain(void)
{
	tmInit();
	tmRow = 24;
	tmColumn = 75;
	tmWrite("Hello, World! = ");

	tmWriteUInt(17);
	tmWrite(" - ");
	tmWriteHex(17);
	tmWrite(" - ");
	tmWriteBin(17);
	tmWrite(" - ");
	tmWriteOct(17);
}