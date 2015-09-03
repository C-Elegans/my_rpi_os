.set FIQ, 0b10001
.set IRQ, 0b10010
.equ SVC, 0b10011
.set SYS, 0b11111
.set MASK, 0b11111

.set GPFSEL0, 0x20200000
.set GPFSEL1, 0x20200004
.set GPSET0, 0x2020001C
.set GPCLR0,  0x20200028
.set TIMER_BASE, 0x20003000
.set CLO, TIMER_BASE + 0x4
.set C1, TIMER_BASE + 0x10
.set INTERRUPT_BASE, 0x2000B000
.set FIQ, INTERRUPT_BASE + 0x20C
.section .data
reg_temp:
	.word 0
	.word 0
light_val:
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
 	ldr r1,=0x100000;
 	ldr r0,=CLO
 	ldr r2,[r0]
 	add r2,r1
 	ldr r0,=C1
 	str r2,[r0]
 	ldr r0,=TIMER_BASE
 	mov r1,#2
 	str r1,[r0]
bx lr

.globl irq_handler
irq_handler:
	push {r0-r12,lr}
	@bl c_handler
	mov r0,#0xab
	bl hexstrings
	mov r0,#0x10000
	bl delayus
	
	pop {r0-r12,lr}
	subs pc,lr,#4

.globl enable_irq
enable_irq:
	set_mode IRQ
	mov sp,#0x3000
	set_mode SYS
    mrs r0,cpsr
    bic r0,r0,#0x80
    msr cpsr_c,r0
    push {lr}
    bl enable_timer
    pop {pc}
