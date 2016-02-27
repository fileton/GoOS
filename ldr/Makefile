#********************************************************
#* 				GoOS Loader - Makefile
#********************************************************
#* Copyright (c) 2016, Gert Nutterts
#* All rights reserved
#*
#* Released under the BSD 3-clause license.
#* https://github.com/nutterts/GoOS/blob/master/LICENSE
#********************************************************/

# Target
TARGET = i686-elf

# Tools
GCC = $(TARGET)-gcc
AS = $(TARGET)-as

# Default options
AOPS = --warn --fatal-warnings
COPS = -Wall -ffreestanding -O2 -nostdlib

# Source objects
OBJS = 	boot.s.o 			\
				ldkernel.s.o	\
				ldr.c.o 			\
				textmode.c.o 	\
				panic.c.o 		\
				cpuid.c.o 		\
				memcpy.c.o 		\
				strlen.c.o 		\
				utoa.c.o 			\
				itoa.c.o 			\
				heap.c.o			\
				memset.c.o		\
				ptkernel.c.o	\

# Built loader
all: clean ldr.elf ldr.asm

# Cleanup
clean:
	rm -rf *.o
	rm -rf *.asm

ldr.asm: ldr.elf
	i686-elf-objdump -d ../iso/boot/ldr.elf > ldr.asm

ldr.elf: $(OBJS)
	mkdir -p ../iso/boot
	$(GCC) -T ldr.ld -o ../iso/boot/ldr.elf $(COPS) $(OBJS) -lgcc
	rm -rf $(OBJS)

# Compile C sources
%.c.o: %.c
	$(GCC) $(COPS) -o $@ -c $< -I.

# Compile assembly sources
%.s.o: %.s
	$(AS) $(AOPS) -o $@ -c $<
