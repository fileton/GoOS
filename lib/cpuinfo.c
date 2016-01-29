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
#include <cpuinfo.h>

void 
cpuinfo_opcode(uint *a, uint *b, uint *c, uint *d)
{

  __asm__ __volatile__ ("cpuid"
         /* Output */ : "=a" (*a), "=b" (*b), "=c" (*c), "=d" (*d)
         /* Input  */ : "a" (*a), "c" (*c) );
}
