#********************************************************
#* 				GoOS Kernel - Makefile
#******************************************************** 
#* Copyright (c) 2016, Gert Nutterts
#* All rights reserved
#*  
#* Released under the BSD 3-clause license.
#* https://github.com/nutterts/GoOS/blob/master/LICENSE
#********************************************************/

# Target
TARGET = x86_64-elf

# Tools
GCC = $(TARGET)-gcc
AS = $(TARGET)-as 	

# Default options
AOPS = --warn --fatal-warnings 
COPS = -O3 -Wall -ffreestanding -mcmodel=kernel -mno-mmx -mno-sse -mno-sse2 -nostdlib

# Source objects
OBJS = boot.s.o krn.c.o

# Built loader
all: clean krn.elf krn.asm

# Cleanup
clean:
	rm -rf *.o
	rm -rf *.asm

krn.asm: krn.elf
	objdump -d ../iso/boot/krn.elf > krn.asm

krn.elf: $(OBJS)
	mkdir -p ../iso/boot
	$(GCC) -T krn.ld -o ../iso/boot/krn.elf $(COPS) $(OBJS) -lgcc -z max-page-size=0x1000
	rm -rf $(OBJS)

# Compile C sources
%.c.o: %.c  
	$(GCC) $(COPS) -o $@ -c $< 

# Compile assembly sources
%.s.o: %.s 
	$(AS) $(AOPS) -o $@ -c $<  