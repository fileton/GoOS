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
#define __LDR_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <cpuid.h>

#include "multiboot.h"
#include "elf64.h"
#include "paging.h"


// Get pointer to base vga ioport
#define bda_vga_ioport (*(volatile uint16_t *)(0x463 & 0xFFFF))

extern void *_heap;
extern void *_text_start;
extern void *_text_end;
extern void *_rodata_start;
extern void *_rodata_end;
extern void *_data_start;
extern void *_data_end;
extern void *_bss_start;
extern void *_bss_end;
extern void *_heap_start;
extern void *_heap_end;

// From assembler
extern void _abort(void);

/*** TEXT MODE ***/

/* Textmode colors */
typedef enum {
	BLACK		  = 0,
	BLUE		  = 1,
	GREEN 		  = 2,
	CYAN  		  = 3,
	RED   		  = 4,
	MAGENTA 	  = 5,
	BROWN 		  = 6,
	LIGHT_GREY	  = 7,
    GREY 		  = 8,
    LIGHT_BLUE 	  = 9,
    LIGHT_GREEN   = 10,
    LIGHT_CYAN 	  = 11,
    LIGHT_RED	  = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN   = 14,
    WHITE 		  = 15
} tmColors;

static const size_t TEXTMODE_HEIGHT = 25;
static const size_t TEXTMODE_WIDTH = 80;

extern size_t 	tmRow;
extern size_t 	tmColumn;
extern uint8_t	tmColor;
extern uint16_t	*tmBuffer;

/* Cursor struct */
typedef struct {
	size_t column;
	size_t row;
} tmCursor_t;


/* Function prototypes */

void 	tmInit		();
void 	tmWriteAt	(char, uint8_t, size_t, size_t);
void	tmWriteChr	(char c);
void 	tmWrite 	(const char *);
void	tmScroll	(void);
void	tmWriteInt	(int64_t);
void	tmWriteUInt	(uint64_t);
void	tmWriteHex	(uint64_t);
void	tmWriteBin	(uint64_t);
void	tmWriteOct	(uint64_t);
void	tmCRLF		(void);
void    tmSetCursor	(size_t, size_t);
bool	tmBoolStr	(bool, char *, char *);

multiboot_module_t 	*findkernel	(multiboot_info_t *);
tmCursor_t 			tmGetCursor (void);

// Make color
inline
uint8_t
tmMakeColor(tmColors fg, tmColors bg)
{
	return fg | bg << 4;
}

// Make entry
inline
uint16_t
tmMakeEntry(char c, uint8_t color)
{
	uint16_t c16 = c;
 	uint16_t cl16 = color;
 	return c16 | cl16 << 8;
}

/*** MISC FUNCTIONS ***/

void 	abort	(void);										// abort execution
void 	*itoa	(int64_t input, char *buffer, int radix); 	// Int to String
void 	*utoa	(uint64_t input, char *buffer, int radix); 	// Unsigned Int to String
size_t	strlen	(const char* str);							// get length of string
void 	memcpy	(void *dst, const void *src, size_t len);	// copy len number of bytes from src to ds

void 	gclPanicString	(char *str);
void 	gclPanicBoolStr	(bool check, char *tstr, char *fstr, char *pstr); 

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