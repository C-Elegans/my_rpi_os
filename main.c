#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028
#include "mem.h"
#include "uart.h"
#include "timer.h"
#include "video.h"
#include "cstdlib.h"

void notmain(){
	int ptr = video_init(); 
	memcpy(ptr, 0x8000, SCREEN_WIDTH * SCREEN_HEIGHT * 2);
}
