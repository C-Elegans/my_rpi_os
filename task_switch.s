.section .context
.globl context_stack
context_stack:
	.skip 0x2000,0
.globl context_storage
context_storage:
	.skip 256,0
.section .text
.globl task_switch
task_switch:
	ldr sp,=context_storage
	stmia sp,{r0-r12}
	cps #0b10011
	
	
	bx lr
