/********************************************************
 * 			GoOS C library - textmode.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <textmode.h>
#include <string.h>
#include <stdlib.h>

size_t 		tmRow;
size_t 		tmColumn;
uint8_t		tmColor;
uint16_t	*tmBuffer;

// Initialize 
void
tmInit(void)
{
	tmRow = 0;
	tmColumn = 75;
    tmColor = tmMakeColor(LIGHT_GREY, BLACK);
    tmBuffer = (uint16_t *) 0xB8000;
}

// Full write
void
tmWriteAt(char c, uint8_t color, size_t row, size_t column)
{
	const size_t index = row * TEXTMODE_WIDTH + column;
	tmBuffer[index] = tmMakeEntry(c, color);
}

// Write character
void
tmWriteChr(char c)
{
	tmWriteAt(c, tmColor, tmRow, tmColumn);

	if (++tmColumn == TEXTMODE_WIDTH)
	{
		tmColumn = 0;
		if (++tmRow == TEXTMODE_HEIGHT)
		{
			tmScroll();
			tmRow--;
		}
	}
}

// Write string
void 
tmWrite(const char* str)
{
	size_t len = strlen(str);
	for (size_t index = 0; index < len; index++ ) tmWriteChr(str[index]);
}

// Scroll the screen by one line
void
tmScroll(void)
{
	size_t index;
	uint16_t empty = tmMakeEntry(' ', tmColor);

	// Copy all lines to the one above them
	for (index = 1; index < TEXTMODE_HEIGHT; index++) 
		memcpy(&tmBuffer[(index-1) * TEXTMODE_WIDTH], &tmBuffer[(index * TEXTMODE_WIDTH)], TEXTMODE_WIDTH * 2);
	
	// Clear lowest line
	for (index = 0; index < TEXTMODE_WIDTH; index++) 
		tmBuffer[(TEXTMODE_HEIGHT - 1) * TEXTMODE_WIDTH + index] = empty; 
}

// Write Int
void
tmWriteInt(int value)
{
	char str[(uint) itoa(value, (char *) 0, 10)];
	itoa(value, (char *) str, 10);
	tmWrite((char *) str);
}

// Write unsigned int
void
tmWriteUInt(uint value)
{
	char str[(uint) utoa(value, (char *) 0, 10)];
	utoa(value, (char *) str, 10);
	tmWrite((char *) str);	
}

// Write hex
void
tmWriteHex(uint value)
{
	char str[(uint) utoa(value, (char *) 0, 16)];
	utoa(value, (char *) str, 16);
	tmWrite("0x");
	tmWrite((char *) str);		
}

// Write binary
void
tmWriteBin(uint value)
{
	char str[(uint) utoa(value, (char *) 0, 2)];
	utoa(value, (char *) str, 2);
	tmWrite((char *) str);			
}

// Write octal
void
tmWriteOct(uint value)
{
	char str[(uint) utoa(value, (char *) 0, 8)];
	utoa(value, (char *) str, 8);
	tmWrite((char *) str);			
}