.set FIQ, 0b10001
.set IRQ, 0b10010
.equ SVC, 0b10011
.set SYS, 0b11111
.set MASK, 0b11111
.section .data
reg_temp:
	.word 0
	.word 0
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
.section .text



.globl enable_timer
enable_timer:
bx lr

.globl irq_handler
irq_handler:
subs pc,lr,#4
