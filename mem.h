//void PUT32(int, int) ;
//void PUT16(int, int);
//void PUT8(int, int);
int GET32(int mem);
int GET8(int mem);
int GETPC();
void dummy();
void led_on();
void led_off();
#ifndef _MEM_H
#define _MEM_H
inline static void PUT32(int addr, int data){
	__asm("str r1,[r0]");
}
inline static void PUT16(int addr, int data){
	__asm("strh r1,[r0]");
}
inline static void PUT8(int addr, int data){
	__asm("strb r1,[r0]");
}
#endif


