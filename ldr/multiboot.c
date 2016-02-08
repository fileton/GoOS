/********************************************************
 *	GoOS Loader - ldr.h
 ******************************************************** 
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *  
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

 #include <ldr.h>

multiboot_module_t *
findkernel(multiboot_info_t *mbinfo)
{
	/* This just a stub that assumes the first module is the kernel. */


	// We're still making sure there accually is a module
	if (mbinfo->flags & (1<<3))
	{
		return (multiboot_module_t *) mbinfo->mods_addr;
	}

	// Kernel not found
	return (multiboot_module_t *) 0;
}
