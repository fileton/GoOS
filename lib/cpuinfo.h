/********************************************************
 *	GoOS C library - cpuid.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#ifndef __CPUID_GCL_H__
#define __CPUID_GCL_H__ 1

#include <cpuid.h>
#include <stdgcl.h>

void cpuid_opcode(uint *a, uint *b, uint *c, uint *d);	// Run opcode


#endif