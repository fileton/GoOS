/********************************************************
 *	GoOS C library - textmode.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

/*
	Provides functions for writing to the VGA textmode
	memory area and controlling the textmode cursor. 
*/

#include <stdgcl.h>

size_t 		tmRow;
size_t 		tmColumn;
uint8_t		tmColor;
uint16_t	*tmBuffer;

// Initialize 
void
tmInit(uint_t vidmem_addr)
{
	tmCursor_t cursor = tmGetCursor();

	tmRow = cursor.row;
	tmColumn = cursor.column;

    tmColor = tmMakeColor(LIGHT_GREY, BLACK);
    tmBuffer = (uint16_t *) vidmem_addr;
}

// Full write
void
tmWriteAt(char c, uint8_t color, size_t row, size_t column)
{
	size_t index = row * TEXTMODE_WIDTH + column;
	tmBuffer[index] = tmMakeEntry(c, color);
}

// Write character
void
tmWriteChr(char c)
{
	switch (c)
	{
	case '\r':
		tmColumn = 0;
		break;
	case '\n':
		if (++tmRow == TEXTMODE_HEIGHT)
		{
			tmScroll();
			tmRow--;
		}	
		break;
	default:
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
	} // switch (c)

	tmSetCursor(tmColumn, tmRow);
}

// Write new line
void
tmCRLF(void)
{
	tmWriteChr(13);
	tmWriteChr(10);
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
tmWriteInt(int_t value)
{
	char str[(uint_t) itoa(value, (char *) 0, 10)];
	itoa(value, (char *) str, 10);
	tmWrite((char *) str);
}

// Write unsigned int
void
tmWriteUInt(uint_t value)
{
	char str[(uint_t) utoa(value, (char *) 0, 10)];
	utoa(value, (char *) str, 10);
	tmWrite((char *) str);	
}

// Write hex
void
tmWriteHex(uint_t value)
{
	char str[(uint_t) utoa(value, (char *) 0, 16)];
	utoa(value, (char *) str, 16);
	tmWrite("0x");
	tmWrite((char *) str);		
}

// Write binary
void
tmWriteBin(uint_t value)
{
	char str[(uint_t) utoa(value, (char *) 0, 2)];
	utoa(value, (char *) str, 2);
	tmWrite((char *) str);			
}

// Write octal
void
tmWriteOct(uint_t value)
{
	char str[(uint_t) utoa(value, (char *) 0, 8)];
	utoa(value, (char *) str, 8);
	tmWrite((char *) str);			
}

// Write bool
void
tmWriteBool(bool value)
{
	if (value)
		tmWrite("true");
	else
		tmWrite("false");
}

// Check bool and write trueStr(ing) or falseStr(ing)
// Returns boolean value 
bool
tmBoolStr(bool value, char *trueStr, char *falseStr)
{
	if (value)
		tmColumn = TEXTMODE_WIDTH - strlen(trueStr) - 2;
	else
		tmColumn = TEXTMODE_WIDTH - strlen(falseStr) - 2;
	
	tmWriteChr('[');
	
	uint8_t oldcolor = tmColor;

	if (value)
	{
		tmColor = tmMakeColor(GREEN, oldcolor >> 4);
		tmWrite(trueStr);
	} else {
		tmColor = tmMakeColor(RED, oldcolor >> 4);
		tmWrite(falseStr);
	}

	tmColor = oldcolor;
	tmWriteChr(']');

	return value;
}

// Write OK/Fail 
void
tmOkFail(bool ok)
{
	if (ok)
		tmColumn = TEXTMODE_WIDTH - 4;
	else
		tmColumn = TEXTMODE_WIDTH - 6;
	
	tmWriteChr('[');
	
	uint8_t oldcolor = tmColor;

	if (ok)
	{
		tmColor = tmMakeColor(GREEN, oldcolor >> 4);
		tmWrite("OK");
	} else {
		tmColor = tmMakeColor(RED, oldcolor >> 4);
		tmWrite("FAIL");
	}

	tmColor = oldcolor;
	tmWriteChr(']');
}

// Write buffer 
void
tmWriteBuffer(char *buffer, size_t len)
{
	for (size_t i = 0; i < len; i++)
		tmWriteChr(buffer[i]);
}

// Set cursor
void
tmSetCursor(size_t column, size_t row)
{
	uint16_t pos = (row * TEXTMODE_WIDTH) + column;
 	uint16_t ioport = bda_vga_ioport;

	outb(ioport, 0x0F);
	io_wait();
 	outb(ioport + 1, (uint8_t) (pos & 0xFF));
 	io_wait();

 	outb(ioport, 0x0E);
 	io_wait();
 	outb(ioport + 1, (uint8_t) ((pos >> 8) & 0xFF));
 	io_wait();
}

// Get cursor
tmCursor_t
tmGetCursor()
{
	uint16_t pos;
	uint16_t ioport = bda_vga_ioport;
	tmCursor_t result;

	outb(ioport, 0x0F);
	io_wait();
	pos = inb(ioport+1);

	outb(ioport, 0x0E);
	io_wait();
	pos += (inb(ioport+1) << 8);

	result.column = pos % TEXTMODE_WIDTH;
	result.row = pos / TEXTMODE_WIDTH;

	return result;
}