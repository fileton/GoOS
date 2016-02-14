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

	tmWrite("Kernel found at ");
	tmWriteHex((uint) krnMod->mod_start);
	tmWrite(".\r\n");

/*** INITIAL PAGE TABLES ***/

	tmWrite("\r\n"); // For readability
  tmWrite("Creating initial page tables for the first 2MiB:\r\n");
	// Highest level - 512GB pages
	uint64_t *pml4 = amalloc(PAGETABLE_SIZE, PAGETABLE_ALIGNMENT);
	memset (pml4, 0, PAGETABLE_SIZE); // Just to be sure

	tmWrite("- PML4 page table at ");
	tmWriteHex((unsigned)pml4);
	tmWrite(".\r\n");

	// Highest 512GB in 1GB pages
	uint64_t *pdp511 = amalloc(PAGETABLE_SIZE, PAGETABLE_ALIGNMENT);
	memset (pdp511, 0, PAGETABLE_SIZE); // Just to be sure

	tmWrite("- PDP page table at ");
	tmWriteHex((unsigned)pdp511);
	tmWrite(" for PML4[511].\r\n");

	pml4[511] = MAKE_PML4E(PAGE_B4B(pdp511), 0, 0, 0, 0, 1, 1);

	// Second to last GB in 2MB pages
	uint64_t *pd511_510 = amalloc(PAGETABLE_SIZE, PAGETABLE_ALIGNMENT);
	memset (pd511_510, 0, PAGETABLE_SIZE);

	tmWrite("- PD page table at ");
	tmWriteHex((unsigned)pd511_510);
	tmWrite(" for PML4[511][510].");

	tmBoolStr(true, "Done", "");
	tmWrite("\r\n"); // For readability

/*** PAGE TABLES FOR KERNEL ***/

	tmWrite("Creating page tables for the kernel:\r\n");


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
