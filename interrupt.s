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
prefetch_vector: .word hang
data_vector:	.word hang
irq_vector: .word hang
fiq_vector: .word hang

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

	
