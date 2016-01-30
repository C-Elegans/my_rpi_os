.section .context
@.globl stack_pointer_storage
stack_pointer_storage:
	.skip 0xA0*4, 0
link_register_storage:
	.skip 0xA0*4, 0
current_task:
	.int 0
task_number:
	.int 1
.section .text
.globl yield
yield:
	stm sp,{r0-lr}^
	mrs r0,spsr
	stmdb sp,{r0,lr}
	add sp,8
	add sp,14*4
	ldr sp,[sp]
	cmp sp,#0
	b hang
	ldmdb sp,{r0,lr}
	msr SPSR,r0
	ldm sp,{r0-lr}^
	subs pc,lr,#4


