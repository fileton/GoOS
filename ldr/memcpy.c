/********************************************************
 *	GoOS Loader - memcpy.c
 ********************************************************
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <ldr.h>



void
memcpy(void *dst, const void *src, size_t len)
{
	size_t index;
	uint8_t *b_dst = (uint8_t *) dst;
	uint8_t *b_src = (uint8_t *) src;

	if (len > 4)
 	{
	  // We have atleast one block of 4 bytes to copy
		size_t i_len = len / 4;
		uintptr_t *i_dst = (uintptr_t *) dst;
		uintptr_t *i_src = (uintptr_t *) src;
		for (index = 0; index < i_len; index++)
		{
			i_dst[index] = i_src[index];
		}

		// Copy remaining bytes (if any)
		size_t b_len = len % 4;
		if (b_len > 0)
		{
			size_t b_offset = i_len * 4;
			size_t b_end = b_offset + b_len;
			for (index = b_offset; index < b_end; index++)
    	{
				b_dst[index] = b_src[index];
			}
		}
	} else {
		// We only have a few bytes to copy
		for (index = 0; index < len; index++) b_dst[index] = b_src[index];
	}
}
