GetSystemTimerBase: 
ldr r0,=0x20003000
mov pc,lr

.globl getTimeStamp
getTimeStamp:
push {lr}
bl GetSystemTimerBase
ldrd r0,r1,[r0,#4]
pop {pc}

.globl delayus
delayus:
delay .req r2
mov delay,r0
push {lr}
bl getTimeStamp
start .req r3
mov start,r0
loop$:
	bl getTimeStamp
	elapsed .req r1
	sub elapsed,r0,start
	cmp elapsed,delay
	.unreq elapsed
	bls loop$
pop {pc}
