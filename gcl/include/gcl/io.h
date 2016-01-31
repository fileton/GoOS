/********************************************************
 *	GoOS C library - io.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

/* Port I/O */

static
inline
void
outw(uint16_t port, uint16_t value)
{
	asm volatile ( "outw %0, %1" : : "a"(value), "Nd"(port) );
}

static
inline
uint16_t
inw(uint16_t port)
{
	uint16_t result;
	asm volatile ( "inw %[port], %[result]" : [result] "=a"(result) : [port] "Nd"(port) );
	return result;
}


/* 	The following three functions where taken from the 
	OSDev wiki under the CC0 v1.0 license on 26 jan 2016. */

static
inline 
void 
outb(uint16_t port, uint8_t value)
{
    asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
}

static
inline 
uint8_t
inb(uint16_t port)
{
    uint8_t result;
    asm volatile ( "inb %[port], %[result]" : [result] "=a"(result) : [port] "Nd"(port) );
    return result;
}

static
inline 
void 
io_wait(void)
{
     asm volatile ( "outb %%al, $0x80" : : "a"(0) );
}

