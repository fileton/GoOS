#********************************************************
#* 					GoOS - Makefile
#******************************************************** 
#* Copyright (c) 2016, Gert Nutterts
#* All rights reserved
#*  
#* Released under the BSD 3-clause license.
#* https://github.com/nutterts/GoOS/blob/master/LICENSE
#********************************************************/


all: clean ldr cdrom 

clean:
	rm -rf iso/* *.iso lib/*.o lib/string/*.o lib/stdlib/*.o
	cd ldr && make clean 

ldr: iso/boot/ldr.elf

cdrom: GoOS.iso

iso/boot/ldr.elf:
	mkdir -p iso/boot
	cd ldr && make all

GoOS.iso: 
	mkdir -p iso/boot/grub
	cp opt/grub.cfg iso/boot/grub/.
	grub-mkrescue -o GoOS.iso iso