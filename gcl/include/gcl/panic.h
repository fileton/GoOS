/********************************************************
 *	GoOS C library - gclpanic.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <stdgcl.h>

/* Write textmode panic string and abort execution */
void gclPanicString(char *str);

/* Extention on tmBoolStr to write panic message and abort execution if 'value' is false. */
void gclPanicBoolStr(bool check, char *tstr, char *fstr, char *pstr); 