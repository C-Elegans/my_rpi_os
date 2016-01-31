#define GPFSEL0 0x20200000
#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028
#define TIMER_BASE 0x20003000
#define CLO	TIMER_BASE + 0x4
#define C1 TIMER_BASE + 0x10
#define INTERRUPT_BASE 0x2000B000
#define FIQ INTERRUPT_BASE + 0x20C
#include "task.h"
#include "mem.h"
#include "uart.h"
#include "timer.h"
#include "video.h"
#include "string.h"
#include "math.h"
#include "interrupt.h"
#include "malloc.h"


volatile int on;
extern int task_stack[];
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
void task1(){
	uart_puts("task1\r\n");
	__asm("svc #0");
}
void notmain(){
	uart_init();
	char* str = "1234567890";
	char* str2 = strchr(str,'4');

	uart_puts(str2);
}
