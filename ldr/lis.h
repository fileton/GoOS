/********************************************************
 *	GoOS Loader - lis.h
 ********************************************************
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/
#ifndef __LIS_H__
#define __LIS_H__ 1

#define LIS_MAGIC 0xB002FEED

struct lis {
  uint32_t magic;         // 0xBOOTFEED
  uint32_t mbinfo;        // addr of multiboot_info_t
  uint32_t pagemap;       // addr of Pagetable root
  uint32_t gdtr;
};
typedef struct lis lis_t;

#endif
