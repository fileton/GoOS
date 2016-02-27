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

/* Function prototypes */
int pkrn_elfmap(elf64_header_t*, elf64_s_header_t, pagemap_t*);

/* Map kernel into virtual address space */
int
ptkernel(multiboot_module_t *krnMod, pagemap_t *pm)
{

  elf64_header_t *elf64 = (elf64_header_t *) krnMod->mod_start;
  if ((elf64->shoff == 0) | (elf64->shnum == 0)) return PTK_ERR_NOLOAD;

  uintptr_t addr = ((unsigned)elf64) + elf64->shoff;
  elf64_s_header_t *elf64_s = (elf64_s_header_t *) addr;
  int error;

  for (int i = 0; i < elf64->shnum; i++)
  {
    if (elf64_s[i].flags & SHF_ALLOC) {
        error = pkrn_elfmap(elf64, elf64_s[i], pm);
        if (error) return error;
    }
  }

  return PTK_NOERROR;
}

/* Create 4K page entry */
int
pkrn_pagemap(pagemap_t *pm, uintptr_t src, uint64_t dst, uint64_t flags)
{
  // Get PDP
  int index = (dst >> 39) & 0x1FF;
  uintptr_t addr;
  pagedirptr_t *pdp;
  pagedir_t *pd;
  pagetable_t *pt;

  if (pm[index].Present)
  {
    addr = pm[index].BaseAddr << 12;
    pdp = ((pagedirptr_t *)(addr));
  }
  else
  {
    pdp = new_pagedirptr();
    pm[index] = entry4pagedirptr(pdp);
  }

  // Get PD
  index = (dst >> 30) & 0x1FF;

  if (pdp[index].Present)
  {
    addr = pdp[index].BaseAddr << 12;
    pd = ((pagedir_t *)(addr));
  }
  else
  {
    pd = new_pagedir();
    pdp[index] = entry4pagedir(pd);
  }

  // Get PT
  index = (dst >> 21) & 0x1FF;

  if (pd[index].Present)
  {
    addr = pd[index].BaseAddr << 12;
    pt = ((pagetable_t *)(addr));
  }
  else
  {
    pt = new_pagetable();
    pd[index] = entry4pagetable(pt);
  }

  // Get PT Entry
  index = (dst >> 12) & 0x1FF;

  if (pt[index].Present)
  {
    // Page shouldn't be present unless it
    // allready points to src.
    if (!(pt[index].PhysicalBaseAddr == (src >> 12)))
    {
      return PTK_ERR_DOUBLEPAGE;
    }
  }
  else
  {
    pt[index].PhysicalBaseAddr = src >> 12;
    pt[index].UserAccess = false;
    pt[index].Writable = ((flags & SHF_WRITE) > 0);
    pt[index].WriteThrough = ((flags & SHF_WRITE) > 0);
    pt[index].NoExecute = !((flags & SHF_EXECINSTR) > 0);
    pt[index].Global = true;
    pt[index].Present = true;
  }

  return PTK_NOERROR;
}

/* Create page table for ELF section */
int
pkrn_elfmap(elf64_header_t* elf64, elf64_s_header_t section, pagemap_t *pm)
{
  uintptr_t src;
  switch (section.type)
  {
  case SHT_PROGBITS:
  {
    src = ((unsigned)elf64) + section.offset;
    break;
  }
  case SHT_NOBITS:
  {
    void *ptr = amalloc(section.size, 4096);
    memset(ptr, 0, section.size);
    src = (unsigned)ptr;
    break;
  }
  default: return PTK_ERR_SECTIONUNKNOWN; // Unknown section that must be allocated
  }

  uint64_t dst = section.addr;
  size_t pages = section.size / (1 << 12);
  if ((pages * (1 << 12)) < section.size) pages++;

  int error;
  for (int i = 0; i < pages; i++)
  {
    error = pkrn_pagemap(pm, src, dst, section.flags);
    if (error) return error;
    src += (1 << 12);
    dst += (1 << 12);
  }

  return PTK_NOERROR;
}
