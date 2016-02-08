#********************************************************
#* 				GoOS Loader - boot.s
#******************************************************** 
#* Copyright (c) 2016, Gert Nutterts
#* All rights reserved
#*  
#* Released under the BSD 3-clause license.
#* https://github.com/nutterts/GoOS/blob/master/LICENSE
#********************************************************/

### MULTIBOOT ###

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

### HEAP ###

# The heap is 512KiB and is located at 0x(FFFFFFF800)180000
# - Contains the loader info structure (LIS)
# - Pagetables used to map the kernel at 0xFFFFFFF800200000 
.section .heap, "aw", @nobits
.skip 0x80000

### STACK ###
.section .stack, "aw", @nobits
.globl _stack_bottom	# bottom of stack
.globl _stack_top		# top of stack

_stack_bottom:
.skip 32768 # 32 KiB
_stack_top:

### ENTRYPOINT ###
.section .text
.globl _start

.type _start, @function
_start:
	# Set stack
	movl $_stack_top, %esp
	
	# Push parameters for our C entrypoint	
	pushl   %ebx	# multiboot info structure
    pushl   %eax	# multiboot magic number
	
	# Call our C entrypoint
	call ldrMain
	
	# Abort execution
	jmp _abort
.size _start, . - _start

### ABORT EXECUTION ###
.section .text
.globl _abort 

.type _abort, @function
_abort:
	cli
	hlt
	jmp _abort
.size _abort, . - _abort
