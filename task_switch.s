.section .text
.globl yield
yield:
	ldr sp,=list_handle
	ldr sp,[sp]
	@mrs r0,cpsr
	@bl hexstring

	@subs pc,lr,#4
	@ldr r0,=yield_str
	@bl uart_puts
	@mov r0,sp
	@bl hexstring
	@mov r0,#0x10000
	@bl delayus
	@mov r0, #0x200000
	@bx r0
	stm sp,{r0-lr}^
	mrs r0,spsr
	stmdb sp,{r0,lr}
	add sp,#8
	add sp,#60 @14*4
	ldr sp,[sp]
	mov sp,r0
	bl hexstring
	cmp sp,#0
	beq hang
	ldmdb sp,{r0,lr}
	msr SPSR,r0
	ldm sp,{r0-lr}^
	subs pc,lr,#4


yield_str:
	.asciz "yield\r\n"