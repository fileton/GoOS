/********************************************************
 *	GoOS Loader - ptkernel.c
 ********************************************************
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <ldr.h>

/* Error codes */
enum {
  PTK_NOERROR = 0,
  PTK_ERR_NOLOAD = 1,
  PTK_ERR_MAP = 1
};

/* Function prototypes */
//bool pkrn_elfmap(elf64_header_t*, elf64_s_header_t, uint64_t*);

/* Map kernel into virtual address space */
/*
int
ptkernel(multiboot_module_t *krnMod, uint64_t *pml4)
{

  elf64_header_t *elf64 = (elf64_header_t *) krnMod->mod_start;
  if ((elf64->shoff == 0) | (elf64->shnum == 0)) return PTK_ERR_NOLOAD;

  tmWrite("\r\n");
  tmWriteHex((unsigned)elf64->shoff);
  tmWrite("\r\n");
  tmWriteHex((unsigned)elf64);
  tmWrite("\r\n");

  uintptr_t addr = ((unsigned)elf64) + elf64->shoff;
  elf64_s_header_t *elf64_s = (elf64_s_header_t *) addr;

  for (int i = 0; i < elf64->shnum; i++)
  {
    switch (elf64_s[i].type)
    {
      case SHT_PROGBITS:
        if (elf64_s[i].flags & SHF_ALLOC) {
          if (!pkrn_elfmap(elf64, elf64_s[i], pml4)) return PTK_ERR_MAP;
        }
        break;
      case SHT_NOBITS:
        tmWrite("NOBITS\r\n");
        break;
    }
  }

  return true;
}
*/
/* Create 4K page entry */
/*
bool
pkrn_pagemap(uint64_t *pml4, uintptr_t src, uint64_t dst, uint64_t flags)
{
  // Get PDP
  int index = (dst >> 39) & 0x1FF;
  uintptr_t addr;
  uint64_t *tbl;
  uint64_t *newTbl;

  if (pml4[index] == 0)
  {
    tbl = (uint64_t*) amalloc(PL_SIZE, PL_ALIGNMENT);
    pml4[index] = PDPE(PL_Addr2Base(tbl), 0, 0, 0, 0, 0, 1, 1);
  } else {
    addr = pml4[index] & PT_BMASK32;
    tbl = (uint64_t *) addr;
  }

  // Get PD
  index = (dst >> 30) & 0x1FF;

  if (tbl[index] == 0)
  {
    newTbl = (uint64_t*) amalloc(PL_SIZE, PL_ALIGNMENT);
    tbl[index] = PD(PL_Addr2Base(newTbl), 0, 0, 0, 0, 0, 1, 1);
    tbl = newTbl;
  } else {
    addr = tbl[index] & PT_BMASK32;
    tbl = (uint64_t *) addr;
  }

  // Get PT
  index = (dst >> 21) & 0x1FF;

  if (tbl[index] == 0)
  {
    newTbl = (uint64_t*) amalloc(PL_SIZE, PL_ALIGNMENT);
    tbl[index] =
    tbl = newTbl;
  } else {
    addr = tbl[index] & PT_BMASK32;
    tbl = (uint64_t *) addr;
  }

  // Get PT Entry
  index = (dst >> 12) & 0x1FF;
  if (tbl[index] == 0) {
    // Create Entry
    tbl[index] = PE()
  } else return false;

  return true;
}
*/
/* Create page table for ELF section */
/*
bool
pkrn_elfmap(elf64_header_t* elf64, elf64_s_header_t section, uint64_t *pml4)
{
  uintptr_t src = ((unsigned)elf64) + section.offset;
  uint64_t dst = section.addr;
  size_t pages = section.size / (1 << 12);
  if ((pages * (1 << 12)) < section.size) pages++;

  for (int i = 0; i < pages; i++)
  {
    src += (i * (1 << 12));
    dst += (i * (1 << 12));
    if (!pkrn_pagemap(pml4, src, dst, section.flags)) return false;
  }

  return true;
}
*/
