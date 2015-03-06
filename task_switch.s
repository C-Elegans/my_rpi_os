.section .context
@.globl stack_pointer_storage
stack_pointer_storage:
	.skip 0xA0*4, 0
link_register_storage:
	.skip 0xA0*4, 0
current_task:
	.int 0
task_number:
	.int 0
.section .text
.globl task_switch
task_switch:
	push {r0,r1}
	ldr r0,=current_task
	ldr r0,[r0]
	ldr r1,=link_register_storage
	str sp,[r1,r0,lsl#2]
	pop {r0,r1}
	cps #0b10011
	@save current context
	push {r0-r12,lr}
	mrs r0,cpsr
	push {r0}
	@store stack pointer
	ldr r0,=current_task
	ldr r0,[r0]
	task .req r0
	ldr r1,=stack_pointer_storage
	str sp,[r1,r0,lsl#2]
	@task arithmatic
	ldr r1=task_number
	ldr r1,[r1]
	add task,#1
	cmp task,r1
	movhs task,#0
	ldr r2,=current_task
	str task,[current_task]
	push {task}
	@next interrupt
	ldr r2,=0x20003000
	ldr r1,[r2,#4]
	add r1,0x1000
	str r1,[r2,#0x10]
	mov r1,#2
	str r1,[r2]
	pop {task}
	ldr r1,=stack_pointer_storage
	ldr sp,[r1,r0,lsl #2]
	pop {r0}
	msr cpsr_c,r0
	pop {r0-r12,lr}
	cps #b10010
	push {r0,r1}
	ldr r0,=current_task
	ldr r0,[r0]
	ldr r1,=link_register_storage
	str sp,[r1,r0,lsl#2]
	pop {r0,r1}
	sub pc, lr, #4
