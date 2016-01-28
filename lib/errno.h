/********************************************************
 * 				GoOS C library - errno.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#ifndef __ERRNO_H__
#define __ERRNO_H__ 1

typedef enum {
	ENOMEM = 1
} errors_t;

static errors_t errno; // Placeholder: Not multithread safe

#endif