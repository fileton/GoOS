/********************************************************
 *	GoOS C library - cpuid.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#ifndef __GCL_CPUID_H__
#define __GCL_CPUID_H__ 1

#include <stdgcl.h>

// Checks if the CPU is supported.
bool cpuid_cpu_supported();

/* Check if cpuid opcode is supported */
static
inline
bool
cpuid_check()
{
	return !(__get_cpuid_max(0, 0) == 0);
}


#endif