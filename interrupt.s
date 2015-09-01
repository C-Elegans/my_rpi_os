.set FIQ, 0b10001
.set IRQ, 0b10010
.equ SVC, 0b10011
.set SYS, 0b11111
.set MASK, 0b11111
.section .data
reg_temp:
	.word 0
	.word 0
.globl task_stack
task_stack:
	.word 0x80000
	.word 0x84000
	.word 0x88000
	.word 0x8c000
	.word 0x90000
	.word 0x94000
	.word 0x98000
	.word 0x9c000
task_sp:
	.word 8
current_task:
	.word 0


.section .text
.macro set_mode mode
	push {r1}
	ldr r1,=reg_temp
	str r0,[r1],#4 @auto increment
	mov r0,r1
	pop {r1}
	str r1,[r0]
	mov r1,r0
	sub r1,#4
	mrs r0,cpsr
	bic r0,# MASK
	orr r0,# \mode
	msr cpsr,r0
	ldr r0,[r1],#4
	ldr r1,[r1]
	
.endm
.globl interrupt
interrupt:
ldr pc,[pc,#20]		@;reset exception
ldr pc,[pc,#20]		@;undef instruction exception
ldr pc,[pc,#20]			@;svc exception
ldr pc,[pc,#20]	@;prefetch abort
ldr pc,[pc,#20]		@;data abort
ldr pc,[pc,#20]			@;irq
ldr pc,[pc,#20]			@;fiq

.globl start_vector
start_vector: .word _start
undef_vector: .word hang
svc_vector:	  .word task_switch
prefetch_vector: .word null_interrupt
data_vector:	.word null_interrupt
irq_vector: .word null_interrupt
fiq_vector: .word null_interrupt

.globl null_interrupt
null_interrupt:
subs pc,lr,#4


.globl enable_interrupts
enable_interrupts:
	ldr   r0,=interrupt
   mov   r1,#0x0000
   ldmia   r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
   stmia   r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
   ldmia   r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
   stmia   r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
   mrs r0,cpsr
   bic r0,r0,#0x80
   msr cpsr_c,r0
   cps #0b10010
   mov sp,#0x4000
   cps #0b10011

   bx lr
.globl add_task
add_task:
	push {r4}
	
	ldr r3,=task_sp
	addr_tasksp .req r3
	ldr r2,[addr_tasksp] 
	tasksp .req r2
	subs tasksp,#1
	movlt pc,lr
	ldr r1,=task_stack
	stack .req r4
	ldr stack,[r1]
	str r0,[stack,#-4]!
	str stack,[r1,tasksp, lsl #2]
	str tasksp,[addr_tasksp]
	pop {r4}
	bx lr
	.unreq tasksp
	.unreq addr_tasksp
	.unreq stack
svc_handler:
	stmdb sp!,{r0-r12,lr}
	mov r4, r0
	ldr r0,=0x20200000
	mov r1,#1
	lsl r1,#16
	cmp r4, #1
	streq r1,[r0,#40]
	strne r1,[r0,#28]
	ldmia sp!,{r0-r12,lr}
	subs pc, lr, #0
.globl led_on
led_on:
	ldr r0,=0x20200000
	mov r1,#1
	lsl r1,#16
	str r1,[r0,#40]
	bx lr
.globl led_off
led_off:
	ldr r0,=0x20200000
	mov r1,#1
	lsl r1,#16
	str r1,[r0,#28]
	bx lr
print_taskstack:
	ldr r4,=task_stack
	mov r5,#0
.loop:	mov r0,r4
		bl hexstring
		add r5,#1
		cmp r5,#8
		blt .loop
	
	bx lr
.globl task_switch
task_switch:
	set_mode SYS
	push {r0-r12,r14}
	set_mode SVC
	mov r0,lr
	set_mode SYS
	push {r0}
	ldr r0,=task_stack
	ldr r2,=current_task
	ldr r1,[r2]
	str sp, [r0,r1,lsl #2]
loop:
	push {r0-r3,lr}
	mov r0,sp
	bl print_taskstack
	pop {r0-r3,lr}	
	add r1,#1
	and r1,#7
	ldr r3,[r0,r1,lsl #2]
	cmp r3,#0
	beq loop
	str r1,[r2]
	mov sp,r3
	pop {r0}
	set_mode SVC
	mov lr,r0
	set_mode SYS
	pop {r0-r12,r14}
	set_mode SVC
	subs pc,lr,#0
	

