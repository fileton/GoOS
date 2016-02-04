/********************************************************
 * 				GoOS Kernel - krn.ld
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

ENTRY(_start)
SECTIONS
{
	. = 0xFFFFFFF80200000;

    .text BLOCK(4K) : ALIGN(4K)
    {
    	_code = .;
        *(.text)
        *(.rodata*)
    }

   .data BLOCK(4K) : ALIGN(4K)
   {
        _data = .;
        *(.data)
   }

   .eh_frame BLOCK(4K) : ALIGN(4K)
   {
       _ehframe = .;
       *(.eh_frame)
   }

   .bss BLOCK(4K) : ALIGN(4K)
   {
       _bss = .;
       *(COMMON)
       *(.bss)
       *(.stack)
   }

   _end = .;
}