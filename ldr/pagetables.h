#ifndef __PAGETABLES_H__
#define __PAGETABLES_H__ 1

#define KRNSPACE 0xFFFFFFF800000000

#define PAGETABLE_ALIGNMENT 1<<12
#define PAGETABLE_SIZE 1<<12


#define PAGE_B4B(addr) (((unsigned)addr) >> 12)
#define PAGE_B4PD(addr) ((((unsigned)addr) >> 21) << 9)


#define MAKE_PML4E(base, avl, pcd, pwt, us, rw, p) \
  (uint64_t)( \
  (base << 12) | \
  (avl << 9) | \
  (pcd << 4) | \
  (pwt << 3) | \
  (us << 2) | \
  (rw << 1) | \
  p)

#define MAKE_PDPE(base, avl, ps, pcd, pwt, us, rw, p) \
  (uint64_t)( \
  (base << 12) | \
  (avl << 9) | \
  (ps << 7) | \
  (pcd << 4) | \
  (pwt << 3) | \
  (us << 2) | \
  (rw << 1) | \
  p)

#define MAKE_PDE(base, avl, g, ps, pcd, pwt, us, rw, p) \
  (uint64_t)( \
  (base << 12) | \
  (avl << 9) | \
  (g << 8) | \
  (ps << 7) | \
  (pcd << 4) | \
  (pwt << 3) | \
  (us << 2) | \
  (rw << 1) | \
  p)


#endif
