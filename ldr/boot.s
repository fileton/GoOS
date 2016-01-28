#********************************************************
#* 				GoOS Loader - boot.s
#******************************************************** 
#* Copyright (c) 2016, Gert Nutterts
#* All rights reserved
#*  
#* Released under the BSD 3-clause license.
#* https://github.com/nutterts/GoOS/blob/master/LICENSE
#********************************************************/

# Declare multiboot constants
.set MAGIC,		0x1BADB002	# magic number
.set ALIGN,    	1<<0		# align loaded modules on page boundaries
.set MEMINFO, 	1<<1		# request memory info

.set FLAGS,    ALIGN | MEMINFO # this is the Multiboot 'flag' field
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Write multiboot header
.section .multiboot 
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Exported symbols
.globl stack_bottom	# bottom of stack
.globl stack_top	# top of stack
.globl HEAP_SIZE	# top of heap
.globl HEAP_START	# bottom of heap
.globl _start		# entrypoint
.globl _abort 		# abort execution

# Allocate space for a stack
.section .stack, "aw", @nobits
stack_bottom:
.skip 32768 # 32 KiB
stack_top:

# Allocate space for a small heap
.section .heap, "aw", @nobits
HEAP_SIZE:
.long 1048576 # size of heap
HEAP_START:
.long . + 1
.skip 1048576 # 1 MiB

# Entrypoint
.section .text
.global _start
.type _start, @function
_start:
	# Set stack
	movl $stack_top, %esp
	
	# Push parameters for our C entrypoint	
	pushl   %ebx	# multiboot info structure
    pushl   %eax	# multiboot magic number
	
	# Call our C entrypoint
	call ldrMain
	
	# Abort execution
	jmp _abort
.size _start, . - _start

# Abort execution
.section .text
.global _start
.type _abort, @function
_abort:
	cli
	hlt
	jmp _abort
.size _abort, . - _abort
