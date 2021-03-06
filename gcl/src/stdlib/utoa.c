/********************************************************
 *	GoOS C library - utoa.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <stdgcl.h>

void 
*utoa(uint_t input, char *buffer, int_t radix)
{
	static char symbols[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	// check if base is within range, if not return null pointer
	if (radix < 2 || radix > 36) return (void *) 0;

	// calculate size of resulting string
	uint_t count = 0;
	int_t value = input;

	// Calculate number of symbols
	do count++; while (value /= radix);	

	// If buffer is null pointer, return size of required buffer
	if (buffer == 0) 
	{
		return (void *) count + 1;
	}
	
	// .. then add the trailing zero
	buffer[count--] = '\0';

	// .. then the symbols
	do buffer[count--] = symbols[input%radix]; while (input/=radix);

	// Return pointer to first char
	return (void *) buffer;
} 
