#define GPFSEL0 0x20200000
#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028
#define TIMER_BASE 0x20003000
#define CLO	TIMER_BASE + 0x4
#define C1 TIMER_BASE + 0x10
#define INTERRUPT_BASE 0x2000B000
#define FIQ INTERRUPT_BASE + 0x20C
#include "mem.h"
#include "uart.h"
#include "timer.h"
#include "video.h"
#include "string.h"
#include "math.h"
volatile int on;
void c_handlerc(){
	if(on){
		led_off();
		on = 0;
	}
	else{
		led_on();
		on = 1;
	}
	PUT32(TIMER_BASE,2); //clear interrupt
	PUT32(C1, GET32(CLO)+1000000);
}
void notmain(){
	//PUT32(GPFSEL0,(1<<12));
	int i;
	on = 0;
	PUT32(TIMER_BASE,2);
	
	PUT32(INTERRUPT_BASE + 0x21c,0xFFFFFFFF);
	PUT32(INTERRUPT_BASE + 0x210,0x2);
	//hexstring(GET32(INTERRUPT_BASE +0x204));
	
	i = GET32(CLO);
	i += 1000000;
	PUT32(C1, i);
	delayus(50000);
	//hexstring(GET32(INTERRUPT_BASE +0x204));
	
}
