/********************************************************
 *	GoOS Loader - ldr.h
 ********************************************************
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#ifndef __LDR_H__
#define __LDR_H__ 1

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <cpuid.h>

#include "pagetables.h"
#include "multiboot.h"
#include "textmode.h"
#include "elf64.h"
#include "lis.h"

typedef unsigned int uint;

// Linker symbols
extern int _text_start;
extern int _text_end;
extern int _rodata_start;
extern int _rodata_end;
extern int _data_start;
extern int _data_end;
extern int _bss_start;
extern int _bss_end;
extern int _heap_start;
extern int _heap_end;

// From assembler
extern void _abort(void);

/*** HEAP ***/
void *malloc(size_t);
void *amalloc(size_t, uint);

/*** MISC FUNCTIONS ***/
#define checkFlag(flags,bit)   ((flags) & (1 << (bit)))

void 	abort	(void);										// abort execution
void*	itoa	(int64_t input, char *buffer, int radix); 	// Int to String
void*	utoa	(uint64_t input, char *buffer, int radix); 	// Unsigned Int to String
void 	memcpy	(void *dst, const void *src, size_t len);	// copy len number of bytes from src to ds
void *memset (void *ptr, int value, size_t num);

void 	gclPanicString	(char *str);
void 	gclPanicBoolStr	(bool check, char *tstr, char *fstr, char *pstr);

size_t	strlen	(const char* str);							// get length of string

/*** I/O ***/

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

/*** CPUID ***/

// Checks if the CPU is supported.
bool cpuid_cpu_supported();

/* Check if cpuid opcode is supported */
static
inline
bool
cpuid_check()
{
	return !(__get_cpuid_max(0, 0) == 0);
}

/*** BOCHS ***/

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

#endif
