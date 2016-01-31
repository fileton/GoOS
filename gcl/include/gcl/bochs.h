/********************************************************
 *	GoOS Loader - bochs.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

/*
	For use with the Bochs Emulator
*/

// Magic Breakpoint
#define BochsMagicBreak() asm volatile ("xchgw %bx, %bx")

// Breakpoint
#define BochsBreak() outw(0x8A00,0x8A00); outw(0x8A00,0x08AE0);

// Write char to debug console
#define BochsWriteChr(c) outb(0xe9, c)

// Write string to debug console
static
inline
void
BochsWrite(char *str)
{
	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++)
		BochsWriteChr(str[i]);
}