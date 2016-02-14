#********************************************************
#*	GoOS - Makefile
#********************************************************
#* Copyright (c) 2016, Gert Nutterts
#* All rights reserved
#*
#* Released under the BSD 3-clause license.
#* https://github.com/nutterts/GoOS/blob/master/LICENSE
#********************************************************/


all: clean ldr krn cd

clean:
	rm -rf iso/boot/* *.iso

ldr: iso/boot/ldr.elf

krn: iso/boot/krn.elf

cd: GoOS.iso

iso/boot/ldr.elf:
	cd ldr && make all

iso/boot/krn.elf:
	cd krn && make all

GoOS.iso:
	mkdir -p iso/boot/grub
	cp grub/grub.cfg iso/boot/grub/.
	grub-mkrescue -o GoOS.iso iso
