/********************************************************
 * 			GoOS C library - textmode.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#ifndef __TEXTMODE_H__
#define __TEXTMODE_H__ 1 

#include <stddef.h>
#include <stdint.h>
#include <stdgcl.h>

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

/* Function prototypes */

void 		tmInit		(void);
void 		tmWriteAt	(char c, uint8_t color, size_t row, size_t column);
void		tmWriteChr	(char c);
void 		tmWrite 	(const char* str);
void		tmScroll	(void);
void		tmWriteInt	(int value);
void		tmWriteUInt	(uint value);
void		tmWriteHex	(uint value);
void		tmWriteBin	(uint value);
void		tmWriteOct	(uint value);

/* Inline functions */

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

#endif