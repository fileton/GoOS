#********************************************************
#* 				GoOS Loader - boot.s
#******************************************************** 
#* Copyright (c) 2016, Gert Nutterts
#* All rights reserved
#*  
#* Released under the BSD 3-clause license.
#* https://github.com/nutterts/GoOS/blob/master/LICENSE
#********************************************************/

# Exported symbols
.globl _stack_bottom	# bottom of stack
.globl _stack_top	# top of stack
.globl _start		# entrypoint
.globl _abort 		# abort execution

# Allocate space for a stack
.section .stack, "aw", @nobits
_stack_bottom:
.skip 65536 # 64 KiB
_stack_top:

# Entrypoint
.section .text
.global _start
.type _start, @function
_start:
	# Set stack
	movabs $_stack_top, %rsp
		
	# Call our C entrypoint
	call main
	
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
