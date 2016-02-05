#define GPFSEL0 0x20200000
#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028
#define TIMER_BASE 0x20003000
#define CLO     TIMER_BASE + 0x4
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
#include "stdlib.h"
#include "list.h"
extern int heap_start;
volatile int on;
extern int task_stack[];
void c_handlerc(){
	if (on) {
		led_off();
		on = 0;
	} else {
		led_on();
		on = 1;
	}
	PUT32(TIMER_BASE, 2); //clear interrupt
	PUT32(C1, GET32(CLO) + 1000000);
}
void task1(){
	//uart_puts("task1\r\n");
	__asm("svc #0");
}
void notmain(){
	uart_init();
	int* intptr = (int*)malloc(sizeof(int));
	*intptr = 1;
	
	struct list* list = create_list(sizeof(int),intptr);
	for(int i=2;i<15;i++){
		intptr =(int*) malloc(sizeof(int));
		*intptr = (unsigned int)rand()% (unsigned int)255;
		add_element(list,sizeof(int),intptr);
	}
	struct list* node = list;
	while (node != NULL) {
		char str[10];
		itoa(*(int*)node->payload,str,10);
		puts(str);
		puts("\r\n");
		node = node->next;
	}
	
}
