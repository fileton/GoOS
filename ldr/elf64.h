/********************************************************
 *	GoOS Loader - elf64.h
 ********************************************************
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#ifndef __ELF64_H__
#define __ELF64_H__ 1

#include <ldr.h>

#define ELF64_MAGIC 0x464C457F

#define ELFCLASS64 0x2
#define ELFDATA2LSB 0x1

#define EM_X86_64 0x3E

enum {
	ET_REL 	= 1,
	ET_EXEC = 2
};

enum {
	SHT_PROGBITS = 1,
	SHT_NOBITS = 8
};

enum {
	SHF_WRITE = 1,
	SHF_ALLOC = 2,
	SHF_EXECINSTR = 4
};

struct elf64_ident {
 	uint32_t 	magic;
 	uint8_t 	class;
 	uint8_t 	data;
 	uint8_t 	version;
 	uint8_t 	osabi;
 	uint8_t 	abiversion;
 	uint8_t 	padding[7];
 };
 typedef struct elf64_ident elf64_ident_t;

struct elf64_header {
	elf64_ident_t ident;
	uint16_t type;
	uint16_t machine;
	uint32_t version;
	uint64_t entry;
	uint64_t phoff;
	uint64_t shoff;
	uint32_t flags;
	uint16_t ehsize;
	uint16_t phentsize;
	uint16_t phnum;
	uint16_t shentsize;
	uint16_t shnum;
	uint16_t shstmdx;
};
typedef struct elf64_header elf64_header_t;

struct elf64_s_header {
	uint32_t name;
	uint32_t type;
	uint64_t flags;
	uint64_t addr;
	uint64_t offset;
	uint64_t size;
	uint32_t link;
	uint32_t info;
	uint64_t addralign;
	uint64_t entsize;
};
typedef struct elf64_s_header elf64_s_header_t;

struct elf64_p_header {
	uint32_t type;
	uint32_t flags;
	uint64_t offset;
	uint64_t vaddr;
	uint64_t paddr;
	uint64_t filesz;
	uint64_t memsz;
	uint64_t align;
};
typedef struct elf64_p_header elf64_p_header_t;

#endif
