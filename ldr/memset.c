/********************************************************
 *	GoOS Loader - memset.c
 ********************************************************
 * Copyright (c) 2016, Gert Nutterts
 * All rights reserved
 *
 * Released under the BSD 3-clause license.
 * https://github.com/nutterts/GoOS/blob/master/LICENSE
 ********************************************************/

#include <ldr.h>

void *
memset (void *ptr, int value, size_t num)
{
  uint8_t chr = (uint8_t) value & 0xFF;
  size_t index;
  uint8_t *b_ptr = (uint8_t *) ptr;

  if (num > 4)
  {
    // We have atleast one block of 4 bytes to set
    uintptr_t bigchr = chr | chr << 8 | chr << 16 | chr << 24;
    size_t i_len = num / 4;
    uintptr_t *i_ptr = (uintptr_t *) ptr;
    for (index = 0; index < i_len; index++) i_ptr[index] = bigchr;

    // Set remaining bytes (if any)
    size_t b_len = num % 4;
    if (b_len > 0)
    {
      size_t b_offset = i_len * 4;
      size_t b_end = b_offset + b_len;
      for (index = b_offset; index < b_end; index++) b_ptr[index] = chr;
    }
  } else {
    // We just have a few bytes to set
    for (index = 0; index < num; index++) b_ptr[index] = chr;
  }

  return ptr;
}
