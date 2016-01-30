/********************************************************
 * 				GoOS C library - stdlib.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#ifndef __STDLIB_H__
#define __STDLIB_H__ 1

#include <stdgcl.h>

void *sbrk	(intptr_t increment);	// Simplest memory manager
void *itoa	(int_t input, char *buffer, int_t radix); 	// Int to String
void *utoa	(uint_t input, char *buffer, int_t radix); 	// Unsigned Int to String

extern uintptr_t HEAP_SIZE;		// Size of heap
extern uintptr_t HEAP_START; 	// Start of heap

#endif