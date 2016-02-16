/********************************************************
 * 				GoOS Loader - ldr.ld
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
	. = 1M;

	.text BLOCK(4K) : ALIGN(4K)
	{
		_multiboot_start = .;
		*(.multiboot)
		_multiboot_end = .;
		_text_start = .;
		*(.text)
		_text_end = .;
	}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		_rodata_start = .;
		*(.rodata)
		_rodata_end = .;
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		_data_start = .;
		*(.data)
		_data_end = .;
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		_bss_start = .;
		*(COMMON)
		. = ALIGN(4K);
		*(.bss)
		. = ALIGN(4K);
		*(.stack)
		_bss_end = .;
	}

	. = 0x180000;
	.heap BLOCK(4K) : ALIGN(4K)
	{
		_heap_start = .;
		*(.heap)
		_heap_end = .;
	}
  _end = .;

  /DISCARD/ :
  {
    *(.comment)
  }
}
