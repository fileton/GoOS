/********************************************************
 *	GoOS C library - gcltypes.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <stdgcl.h>

#ifdef __x86_64__
 
	#define int_t 	int64_t 
	#define uint_t 	uint64_t 

#else // Assumes i686 if not x86_64
 
	#define int_t 	int32_t 
 	#define uint_t 	uint32_t 

#endif

typedef unsigned int uint;