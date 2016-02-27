#********************************************************
#* 				GoOS Loader - ldkernel.s
#********************************************************
#* Copyright (c) 2016, Gert Nutterts
#* All rights reserved
#*
#* Released under the BSD 3-clause license.
#* https://github.com/nutterts/GoOS/blob/master/LICENSE
#********************************************************/

# We can't jump directly from compatibility mode into our kernel
# because it's above 4GiB. So we need some 64bit code in our 32bit loader
# that performs the jump to 0xFFFFFFFF80200000.
#
# The trampoline function below disassembles to:
# 0:	48 31 c0             	xor    %rax,%rax
# 3:	66 b8 10 00          	mov    $0x10,%ax
# 7:	8e d8                	mov    %eax,%ds
# 9:	8e c0                	mov    %eax,%es
# b:	8e e0                	mov    %eax,%fs
# d:	8e e8                	mov    %eax,%gs
# f:	8e d0                	mov    %eax,%ss
# 11:	48 c7 c0 00 00 20 80 	mov    $0xffffffff80200000,%rax
# 18:	ff e0                	jmpq   *%rax

.section .text
.globl _trampoline
.type _trampoline, @function
_trampoline:
  .long 0x66C03148
  .long 0x8E0010B8
  .long 0x8EC08ED8
  .long 0x8EE88EE0
  .long 0xC0C748D0
  .long 0x80200000
  .word 0xE0FF
.size _trampoline, . - _trampoline

# A simple GDT to start our kernel
.section .data
_GDT:
# NULL
  .quad 0
# CODE SEGMENT
  .word 0
  .word 0
  .byte 0
  .byte 0x9A
  .byte 0x20
  .byte 0
# DATA SEGMENT
  .word 0
  .word 0
  .byte 0
  .byte 0x92
  .byte 0
  .byte 0
_GDTR:
  .word 24
  .long _GDT
  .long 0


.section .text
.globl _ldkernel
.type _ldkernel, @function
_ldkernel:
# Set PAE bit in CR4
  movl %cr4, %eax
  orl $0x20, %eax
  movl %eax, %cr4

# Set LM bit
  movl $0xC0000080, %ecx
  rdmsr
  or $0x100, %eax
  wrmsr

# Set CR3 to PML4
  movl 4(%esp), %eax
  movl %eax, %cr3

# Enable paging
  movl %cr0, %eax
  orl 1<<31, %eax
  movl %eax, %cr0

# Load new GDT
  lgdt (_GDTR)

# Jump to trampoline
  jmpl $8, $_trampoline
  ret
.size _ldkernel, . - _ldkernel
