/********************************************************
 * 				GoOS C library - memcpy.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/


/* 
	A simple memcpy implemenation that isn't safe for overlapping data..
*/

#include <stddef.h>
#include <stdint.h>

void 
memcpy(void *dst, const void *src, size_t len)
{
	size_t uintptr_size = sizeof(uintptr_t);
	size_t index;
	
	size_t i_len = len / uintptr_size;
	size_t b_len = len;

	// Copy in blocks of 4 or 8 bytes. 
	if (i_len > 0)
	{
		uintptr_t *i_dst = (uintptr_t *) dst;
		uintptr_t *i_src = (uintptr_t *) src;
		for (index = 0; index < i_len; index++) i_dst[index] = i_src[index];
		b_len = len - (i_len * uintptr_size);
	} 

	// Copy the remaining bytes
	if (b_len > 0)
	{
		char *c_dst = (char *) dst;
		char *c_src = (char *) src;
		for (index = 0; index < len; index++) c_dst[index] = c_src[index];
	}
}