/********************************************************
 *	GoOS C library - stdgcl.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#ifndef __STDGCL_H__
#define __STDGCL_H__ 1

#include <stdint.h>

typedef unsigned int uint;

/* I/O  */

// Byte I/O out
// Taken from the OSDev.org Wiki under the CC0 1.0 license.
// http://creativecommons.org/publicdomain/zero/1.0/
inline 
void 
outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

// Byte I/O in
// Taken from the OSDev.org Wiki under the CC0 1.0 license.
// http://creativecommons.org/publicdomain/zero/1.0/
inline 
uint8_t
inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %[port], %[result]" : [result] "=a"(ret) : [port] "Nd"(port) );
    return ret;
}

// Dummy I/O out
// Taken from the OSDev.org Wiki under the CC0 1.0 license.
// http://creativecommons.org/publicdomain/zero/1.0/
inline 
void 
io_wait(void)
{
     asm volatile ( "outb %%al, $0x80" : : "a"(0) );
}

#endif
