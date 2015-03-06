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
svc_vector:	  .word svc_handler
prefetch_vector: .word hang
data_vector:	.word hang
irq_vector: .word hang
fiq_vector: .word irq_handler

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
   ldr r0,=0x20200000
   mov r1,#7
   lsl r1,#18
   ldr r2,[r0,#4]
   bic r2, r1
   mov r1,#1
   lsl r1,#18
   orr r2,r1
   str r2,[r0,#4]
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
irq_handler:
	stmdb sp!,{r0-r12,lr}
	ldr r3,=delay
	ldr r4,[r3]
	add r4,r4,#1
	cmp r4,#50
	movls r4,#50
	cmp r4,#0x0C00
	movhi r4,#50
	strh r4,[r3]
	lsl r4,#1
	mov r0,r4
	
	ldr r2,=0x20003000
	ldr r1,[r2,#4]
	add r1,r4
	str r1,[r2,#0x10]
	mov r1,#2
	str r1,[r2]
	ldr r0,=0x20200000
	ldr r1,=gpio4
	ldr r2,[r1]
	eor r2,r2,#1
	str r2,[r1]
	mov r1,#1
	lsl r1,#4
	cmp r2,#1
	streq r1,[r0, #28]
	strne r1,[r0, #40]
	ldmia sp!,{r0-r12,lr}
	subs pc, lr, #4

.section .data
.globl gpio4
gpio4:
	.int 0
.globl delay
delay:
	.int 10
