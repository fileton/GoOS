/********************************************************
 * 				GoOS C library - sbrk.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

uintptr_t sbrk_pos = 0;

void 
*sbrk(intptr_t increment)
{
	if (sbrk_pos == 0) sbrk_pos = HEAP_START;
	if ((sbrk_pos + increment) > (HEAP_START + HEAP_SIZE)) 
	{
		errno = ENOMEM;
		return (void *) -1;
	}
	uintptr_t result = sbrk_pos;
	sbrk_pos += increment;
	return (void *) result;
}