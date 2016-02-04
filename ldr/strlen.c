/********************************************************
 *	GoOS Loader - strlen.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <ldr.h>

 size_t
 strlen(const char* str)
 {
	size_t len = 0;
	while (str[len] != 0 ) len++;
	return len;
}