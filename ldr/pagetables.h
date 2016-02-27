#ifndef __PAGETABLES_H__
#define __PAGETABLES_H__ 1

#include <ldr.h>

/* MEMORY ALLOCATION */

static
inline
void *
page_alloc()
{
  void *result = amalloc(4096, 4096);
  return memset(result, 0, 4096);
}

/* PAGE MAP LEVEL 4 */

union pagemap_entry {
  struct {
    uint64_t Present : 1;
    uint64_t Writable : 1;
    uint64_t UserAccess : 1;
    uint64_t WriteThrough : 1;
    uint64_t CacheDisable : 1;
    uint64_t Accessed : 1;
    uint64_t _ignore : 3;
    uint64_t LowAvail : 3;
    uint64_t BaseAddr : 40;
    uint64_t HighAvail : 11;
    uint64_t NoExecute : 1;
  };
  uint64_t Entry;
};

typedef union pagemap_entry pagemap_t;
#define new_pagemap() ((pagemap_t*)(page_alloc()))

/* PAGE DIRECTORY POINTER */

union pagedirptr_entry {
  struct {
    uint64_t Present : 1;
    uint64_t Writable : 1;
    uint64_t UserAccess : 1;
    uint64_t WriteThrough : 1;
    uint64_t CacheDisable : 1;
    uint64_t Accessed : 1;
    uint64_t Dirty : 1;
    uint64_t PageSize : 1;
    uint64_t Global : 1;
    uint64_t LowAvail : 3;
    uint64_t BaseAddr : 40;
    uint64_t HighAvail : 11;
    uint64_t NoExecute : 1;
  };
  struct {
    uint64_t _ignore1 : 12;
    uint64_t PageAttributeTable : 1;
    uint64_t _ignore2 : 17;
    uint64_t PhysicalBaseAddr : 22;
  };
  uint64_t Entry;
};

typedef union pagedirptr_entry pagedirptr_t;
#define new_pagedirptr() ((pagedirptr_t*)(page_alloc()))

static
inline
pagemap_t
entry4pagedirptr(pagedirptr_t *pdp)
{
  pagemap_t result;
  result.BaseAddr = ((unsigned)(pdp)) >> 12;
  result.Present = true;
  result.Writable = true;
  result.UserAccess = true;
  return result;
}

/* PAGE DIRECTORY */

union pagedir_entry {
  struct {
    uint64_t Present : 1;
    uint64_t Writable : 1;
    uint64_t UserAccess : 1;
    uint64_t WriteThrough : 1;
    uint64_t CacheDisable : 1;
    uint64_t Accessed : 1;
    uint64_t Dirty : 1;
    uint64_t PageSize : 1;
    uint64_t Global : 1;
    uint64_t LowAvail : 3;
    uint64_t BaseAddr : 40;
    uint64_t HighAvail : 11;
    uint64_t NoExecute : 1;
  };
  struct {
    uint64_t _ignore1 : 12;
    uint64_t PageAttributeTable : 1;
    uint64_t _ignore2 : 7;
    uint64_t PhysicalBaseAddr : 31;
  };
  uint64_t Entry;
};

typedef union pagedir_entry pagedir_t;
#define new_pagedir() ((pagedir_t*)(page_alloc()))

static
inline
pagedirptr_t
entry4pagedir(pagedir_t *pd)
{
  pagedirptr_t result;
  result.BaseAddr = ((unsigned)(pd)) >> 12;
  result.Present = true;
  result.Writable = true;
  result.UserAccess = true;
  return result;
}

/* PAGE TABLE */

union pagetable_entry {
  struct {
    uint64_t Present : 1;
    uint64_t Writable : 1;
    uint64_t UserAccess : 1;
    uint64_t WriteThrough : 1;
    uint64_t CacheDisable : 1;
    uint64_t Accessed : 1;
    uint64_t Dirty : 1;
    uint64_t PageAttributeTable : 1;
    uint64_t Global : 1;
    uint64_t LowAvail : 3;
    uint64_t PhysicalBaseAddr : 40;
    uint64_t HighAvail : 11;
    uint64_t NoExecute : 1;
  };
  uint64_t Entry;
};

typedef union pagetable_entry pagetable_t;
#define new_pagetable() ((pagetable_t*)(page_alloc()))

static
inline
pagedir_t
entry4pagetable(pagetable_t *pt)
{
  pagedir_t result;
  result.BaseAddr = ((unsigned)(pt)) >> 12;
  result.Present = true;
  result.Writable = true;
  result.UserAccess = true;
  return result;
}

#endif
