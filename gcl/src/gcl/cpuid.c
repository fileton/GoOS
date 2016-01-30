/********************************************************
 *	GoOS C library - cpuid.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <stdgcl.h>

/* 
	Various functions for getting detailed CPU information.
*/

/* Check if it's an Intel CPU  */
bool
cpuinfo_isIntel()
{
	unsigned int a = 0, b = 0, c = 0, d = 0;
	
	__get_cpuid(0, &a, &b, &c, &d);

	return ((b == signature_INTEL_ebx) && \
			(c == signature_INTEL_ecx) && \
			(d == signature_INTEL_edx));
}