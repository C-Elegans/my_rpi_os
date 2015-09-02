.globl _start
_start:
	mov sp,#0x8000
	@bl enable_interrupts
	@bl start_l1cache

	@;svc #0
	bl notmain
	mov r0,#0x18000
	bl delayus
	mov r0, #0x200000
	bx r0

.globl start_l1cache
start_l1cache:
    mov r0, #0
    mcr p15, 0, r0, c7, c7, 0 ;@ invalidate caches
    mcr p15, 0, r0, c8, c7, 0 ;@ invalidate tlb
    mrc p15, 0, r0, c1, c0, 0
    orr r0,r0,#0x1000 ;@ instruction
    orr r0,r0,#0x0004 ;@ data
    mcr p15, 0, r0, c1, c0, 0
    bx lr

.globl hang
hang:
	ldr r0,=0x20200000
	mov r1,#1
	lsl r1,#18
	str r1,[r0,#4]
	mov r1,#1
	lsl r1,#16
	str r1,[r0,#40]
hang$:
	b hang$
.globl dummy
dummy:
	bx lr
;@.globl PUT32
;@PUT32:
;@	str r1,[r0]
;@	bx lr
.globl PUT16
PUT16:
	strh r1,[r0]
	bx lr
.globl PUT8
PUT8:
	strb r1,[r0]
	bx lr
.globl GET32
GET32:
    ldr r0,[r0]
    bx lr
.globl GET8
GET8:
	ldrb r0,[r0]
	bx lr
.globl GETPC
GETPC:
	mov r0,lr
	bx lr
.globl enable_irq
enable_irq:
    mrs r0,cpsr
    bic r0,r0,#0x80
    msr cpsr_c,r0
    bx lr
