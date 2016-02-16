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

lis_t *lis;

/*** FUNCTION PROTOTYPES */
// implementations are below entrypoint
inline void initLis(multiboot_info_t *);
inline void sanityCheck(uint);
inline multiboot_module_t* getKrnMod(multiboot_info_t *);

/*** ENTRYPOINT ***/
void
ldrMain(uint magic, multiboot_info_t *mbinfo)
{
	tmInit();						// Initialize textmode
	sanityCheck(magic);	// Make sure we can load the kernel
	initLis(mbinfo);	 	// Initialize loader info structure

/*** FIND KERNEL ***/

	tmWrite("Searching for module containing the kernel.");

	multiboot_module_t *krnMod = getKrnMod(mbinfo);
	gclPanicBoolStr(!(krnMod == NULL), "Found", "Fail", "Kernel not found.");

/** PAGING **/

	tmWrite("Creating page tables for first 2MiB and the kernel.");

	// Create tables
	pagemap_t *pml = new_pagemap();
	pagedirptr_t *pdp = new_pagedirptr();
	pagedir_t *pd = new_pagedir();
	pagetable_t *pt = new_pagetable();

	// Link them together
	pml[511] = entry4pagedirptr(pdp);
	pdp[510] = entry4pagedir(pd);
	pd[0] = entry4pagetable(pt);

	// Map first 2MiB
	//- Doing it in 4K pages instead of one 2M page so
	//- we can reuse free pages later on.
	for (int i = 0; i < 512; i++) {
		pt[i].Present = true;
		pt[i].Writable = true;
		pt[i].WriteThrough = true;
		pt[i].UserAccess = false;
		pt[i].PhysicalBaseAddr = true;
	}

	// Put page map in LIS
	lis->pagemap += (unsigned)pml;






//	lis->pml4 += (unsigned)pml4;

//	/* Kernel */
//	bool error = ptkernel(krnMod, pml4);

//	gclPanicBoolStr(!error, "Done", "Fail", "");

 };


/*** FUNCTIONS ***/

/* Get kernel module */
inline
multiboot_module_t*
getKrnMod(multiboot_info_t *mbinfo)
{
	multiboot_module_t *mod;
	elf64_header_t *elf64;
	int i;


	if (checkFlag(mbinfo->flags, 3) && (mbinfo->mods_count > 0))
	{
		for (
					i = 0, mod = (multiboot_module_t *) mbinfo->mods_addr;
					i < mbinfo->mods_count;
					i++, mod++
				)
		{
			elf64 = (elf64_header_t *) mod->mod_start;
			if (
					(elf64->ident.magic == ELF64_MAGIC) &
					(elf64->ident.class == ELFCLASS64) &
					(elf64->ident.data == ELFDATA2LSB) &
					(elf64->machine == EM_X86_64) &
					(elf64->entry == (KRNSPACE + 0x200000))
			) return mod;
		} // for
	} // if

	return NULL;
};

/* Initialize loader info structure */
inline
void
initLis(multiboot_info_t *mbinfo)
{
	// malloc must return 0x180000
	lis = (lis_t *) malloc(sizeof(lis_t));
  // set magic
	lis->magic = LIS_MAGIC;
	// 64bit addr of multiboot_info_t
	lis->mbinfo = ((uint32_t) mbinfo) + KRNSPACE;
	// Preset page table root to krnspace
	lis->pagemap = KRNSPACE;
};

/* Check that the CPU supports the kernel */
inline
void
sanityCheck(uint magic) {
	// Check for multiboot loader
	tmWrite("Compatible bootloader?");
	gclPanicBoolStr(magic == MULTIBOOT_BOOTLOADER_MAGIC, "Yes", "No", "A multiboot compatible bootloader is required.");

	// Is it a 64bit cpu from Intel or AMD?
	tmWrite("CPU supported?");
	gclPanicBoolStr(cpuid_cpu_supported(), "Yes", "No", "Sorry, only 64bit CPU's from Intel or AMD are supported.");
};
