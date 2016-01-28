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

# Library objects
LIBOBJS = ../lib/textmode.c.ldr.o ../lib/string/strlen.c.ldr.o ../lib/string/memcpy.c.ldr.o ../lib/stdlib/utoa.c.ldr.o ../lib/stdlib/itoa.c.ldr.o

# Source objects
OBJS = boot.s.ldr.o ldr.c.ldr.o

# Built loader
all: ldr.elf ldr.asm

# Cleanup
clean:
	rm -rf *.ldr.o
	rm -rf *.asm

ldr.asm: ldr.elf
	objdump -d ../iso/boot/ldr.elf > ldr.asm

ldr.elf: $(LIBOBJS) $(OBJS)
	$(GCC) -T ldr.ld -o ../iso/boot/ldr.elf $(COPS) $(OBJS) $(LIBOBJS) -lgcc

# Compile C sources
%.c.ldr.o: %.c  
	$(GCC) $(COPS) -o $@ -c $< -I. -I../lib

# Compile assembly sources
%.s.ldr.o: %.s 
	$(AS) $(AOPS) -o $@ -c $< -I. -I../lib