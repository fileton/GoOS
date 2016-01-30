#********************************************************
#*	GoOS - Makefile
#******************************************************** 
#* Copyright (c) 2016, Gert Nutterts
#* All rights reserved
#*  
#* Released under the BSD 3-clause license.
#* https://github.com/nutterts/GoOS/blob/master/LICENSE
#********************************************************/


all: clean lib ldr cd 

clean:
	rm -rf iso/* *.iso

ldr: iso/boot/ldr.elf

cd: GoOS.iso

lib:
	cd gcl && make TARGET=i686
	cd gcl && make TARGET=x86_64

iso/boot/ldr.elf:
	mkdir -p iso/boot
	cd ldr && make all

GoOS.iso: 
	mkdir -p iso/boot/grub
	cp opt/grub.cfg iso/boot/grub/.
	grub-mkrescue -o GoOS.iso iso