/********************************************************
 *	GoOS Loader - krn.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include "krn.h"
#include "stdint.h"

void
main(void)
{	
	uint8_t *v = (uint8_t *) 0xFFFFFFF8000B8000;
	v[0] = '@';
}

// 0xFFFFFFF8000B8000
