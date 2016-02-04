/********************************************************
 *	GoOS Loader - cpuid.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <ldr.h>

/* Checks if the CPU is supported */
bool
cpuid_cpu_supported()
{
	// Check if it has the cpuid feature
	if (!cpuid_check()) return false;

	// Get vendor id 
	unsigned int a = 0, b = 0, c = 0, d = 0;
	__get_cpuid(0, &a, &b, &c, &d);

	// Check if it's Intel or AMD
	if (!((	(b == signature_INTEL_ebx) && 	\
			(c == signature_INTEL_ecx) && 	\
			(d == signature_INTEL_edx) 		\
		) || ( 								\
			(b == signature_AMD_ebx) && 	\
			(c == signature_AMD_ecx) &&		\
			(d == signature_AMD_edx)		\
		) )) return false;

	// Check if it supported extended cpuid info
	if (__get_cpuid_max(0x80000000, 0)  < 1) return false;
	
	// Check it supports 64bit
	__get_cpuid(0x80000001, &a, &b, &c, &d);
	return (d  & bit_LM) > 0;
}