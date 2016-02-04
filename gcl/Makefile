#********************************************************
#*	GoOS C Library - Makefile
#******************************************************** 
#* Copyright (c) 2016, Gert Nutterts
#* All rights reserved
#*  
#* Released under the BSD 3-clause license.
#* https://github.com/nutterts/GoOS/blob/master/LICENSE
#********************************************************/

ifndef TARGET
$(error TARGET is undefined. Should be either TARGET=i686 or TARGET=x86_64)
endif

ifeq ($(TARGET),i686)
# i686-elf compile options
#
# Compiles a subset of the GCL for the loader
AOPS = --warn --fatal-warnings
COPS = -Wall -ffreestanding -O3 -nostdlib
C_OBJS = 	src/gcl/textmode.c.o \
			src/gcl/cpuid.c.o \
			src/gcl/panic.c.o \
			src/stdlib/utoa.c.o \
			src/stdlib/itoa.c.o \
			src/string/memcpy.c.o \
			src/string/strlen.c.o
VALID_TARGET = 1
endif

ifeq ($(TARGET), x86_64)
#
# x86_64-elf compile options
#
# Will compile the entire GCL for the kernel

AOPS = --warn --fatal-warnings
COPS = -O3 -Wall -ffreestanding -mcmodel=kernel -gdwarf2 -mno-mmx -mno-sse -mno-sse2 -nostdlib
C_OBJS = $(shell find src -type f -name "*.c" | xargs | sed 's/\.c/\.c\.o/g')
VALID_TARGET = 1
endif

ifneq ($(VALID_TARGET), 1)
$(error Not a valid target. Specify either i686 or x86_64)
endif

# Toolset
GCC = $(TARGET)-elf-gcc
AS = $(TARGET)-elf-as
LD = $(TARGET)-elf-ld
OBJDUMP = $(TARGET)-elf-objdump

all: clean $(C_OBJS)
	$(LD) -r $(C_OBJS) -o lib/gcj-$(TARGET).lib
	rm -rf $(C_OBJS)
	$(OBJDUMP) -d lib/gcj-$(TARGET).lib > lib/gcj-$(TARGET).asm

clean:
	rm -rf $(C_OBJS)
	rm -rf lib/gcj-$(TARGET).*

# Compile rules
%.c.o: %.c  
	$(GCC) $(COPS) -o $@ -c $< 

%.s.o: %.s 
	$(AS) $(AOPS) -o $@ -c $<