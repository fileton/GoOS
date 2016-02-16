/********************************************************
 *	GoOS Loader - panic.c
 ********************************************************
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <ldr.h>

/* Abort execution */
void
gclAbort(void)
{
	_abort();
}

/* Textmode Panic String */
void
gclPanicString(char *str)
{
	tmColor = tmMakeColor(RED, BLACK);
	tmWriteChr('[');
	tmColor = tmMakeColor(WHITE, BLACK);
	tmWrite("Panic: ");
	tmColor = tmMakeColor(LIGHT_GREY, BLACK);
	tmWrite(str);
	tmColor = tmMakeColor(RED, BLACK);
	tmColumn = 79;
	tmWriteChr(']');
	gclAbort();
}

/* Extention on tmBoolStr to write panic message and abort execution if 'value' is false. */

void
gclPanicBoolStr(bool check, char *tstr, char *fstr, char *pstr)
{
	if (!tmBoolStr(check, tstr, fstr))
	{
		gclPanicString(pstr);
	}
}
