/********************************************************
 *	GoOS Loader - ldr.c
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include "ldr.h"

void
ldrMain(unsigned int magic, multiboot_info_t *mbinfo)
{	
	// Init textmode
	tmInit();

	// Check for multiboot loader
	tmWrite("Compatible bootloader?");
	gclPanicBoolStr(magic == MULTIBOOT_BOOTLOADER_MAGIC, "Yes", "No", "A multiboot compatible bootloader is required.");

	// Is it a 64bit cpu from Intel or AMD?
	tmWrite("CPU supported?");
	gclPanicBoolStr(cpuid_cpu_supported(), "Yes", "No", "Sorry, only 64bit CPU's from Intel or AMD are supported.");

	// Find kernel
	tmWrite("Searching for the kernel.");
	// - Find module containing kernel
	multiboot_module_t *krn = findkernel(mbinfo);
	// - Panic if not found
	gclPanicBoolStr(!((krn == 0)), "Found", "Fail", "Kernel not found.");
	// - Print kernel info
	tmWrite("Kernel located at ");
	tmWriteHex(krn->mod_start);
	tmWrite(", size=");
	tmWrite("\r\n");

	//elf64_header_t *header = (elf64_header_t *) krn->mod_start;

	tmWrite("_text_start = ");
	tmWriteHex((unsigned)&_text_start);
	tmWrite("\r\n");
	tmWrite("_text_end = ");
	tmWriteHex((unsigned)&_text_end);
	tmWrite("\r\n");

	tmWrite("_rodata_start = ");
	tmWriteHex((unsigned)&_rodata_start);
	tmWrite("\r\n");
	tmWrite("_rodata_end = ");
	tmWriteHex((unsigned)&_rodata_end);
	tmWrite("\r\n");

	tmWrite("_data_start = ");
	tmWriteHex((unsigned)&_data_start);
	tmWrite("\r\n");
	tmWrite("_data_end = ");
	tmWriteHex((unsigned)&_data_end);
	tmWrite("\r\n");

	tmWrite("_bss_start = ");
	tmWriteHex((unsigned)&_bss_start);
	tmWrite("\r\n");
	tmWrite("_bss_end = ");
	tmWriteHex((unsigned)&_bss_end);
	tmWrite("\r\n");

	tmWrite("_heap_start = ");
	tmWriteHex((unsigned)&_heap_start);
	tmWrite("\r\n");

	tmWrite("_heap_end = ");
	tmWriteHex((unsigned)&_heap_end);
	tmWrite("\r\n");
}