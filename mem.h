inline static void PUT32(int, int) ;
inline static void PUT16(int, int);
inline static void PUT8(int, int);
inline static int GET32(int mem);
inline static int GET8(int mem);
inline static int GETPC();
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
inline static int GET32(int mem){
	register int *ret __asm("r0");
	__asm("ldr r0,[r0]");
	return *ret;
}
inline static int GET8(int mem){
	register int *ret __asm("r0");
	__asm("ldrb r0,[r0]");
	return *ret;
}
inline static int GETPC(){
	register int *ret __asm("r0");
	__asm("mov r0,pc");
	return *ret;
}
#endif


