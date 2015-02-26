.globl _start
_start:
	mov sp,#0x8000
	bl notmain
	mov r0, #0x200000
	bx r0

.globl dummy
dummy:
	bx lr
.globl PUT32
PUT32:
	str r1,[r0]
	bx lr
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
