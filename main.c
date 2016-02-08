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
#include "graphics.h"
#include "color.h"
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
	puts("Starting\r\n");
	
	short* video_fb = video_init();
	memset(video_fb, 0x0001,SCREEN_WIDTH * SCREEN_HEIGHT*2);
	set_pixel(video_fb, 320,200,WHITE);
	line(video_fb,(ivec2) {0,0},(ivec2){100,100},WHITE);
	ivec2 a =(ivec2){200,200};
	ivec2 b =(ivec2){400,90};
	ivec2 c =(ivec2){550,450};
	//set_pixel(video_fb,a,WHITE);
	triangle(video_fb,a,b,c,YELLOW);
	
}
