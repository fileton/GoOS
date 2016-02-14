
#include <ldr.h>

size_t heap_offset = (size_t) &_heap_start;
size_t heap_end = (size_t) &_heap_end;

// Return pointer for 'size' bytes
void *
malloc(size_t size)
{
  if ((heap_offset + size) < heap_end)
  {
    void *result = (void *) heap_offset;
    heap_offset += size;
    return result;
  }
  gclPanicString("Out of heap.");
  return (void *) 0;
}

void *
amalloc(size_t size, uint alignment)
{
  size_t misalign = heap_offset % alignment;
  if (misalign > 0) malloc(alignment - misalign);
  return malloc(size);
}
