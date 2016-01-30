/********************************************************
 * 				GoOS C library - string.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#ifndef __STRING_H__
#define __STRING_H__ 1

size_t	strlen	(const char* str);							// get length of string
void 	memcpy	(void *dst, const void *src, size_t len);	// copy len number of bytes from src to ds

#endif