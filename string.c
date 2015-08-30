#include "string.h"
#include "uart.h"

void *memset(int ptr, int c, int size){

	if(size > 3){
		int c2 = (c | (c<<8) | (c<<16) | (c<<24));
		int x;
		for(x = ptr + size; x > ptr + 3; x-=4){
			//PUT32(x,c2);
			__asm("str %[c2],[%[x]]"::[c2] "r" (c2), [x] "r" (x));
		}
		for(;x>ptr;x--){
			PUT8(x,c);
		}
	}
	else{
		for(int x = ptr + size; x > ptr; x--){
			PUT8(x,c);
		}
	}
	return (void *) ptr;
}
void *fast_memset(int ptr, int c, int size){

	if(size > 3){
		int c2 = (c | (c<<8) | (c<<16) | (c<<24));
		int x;
		for(x = ptr + size; x > ptr + 3; x-=4){
			//PUT32(x,c2);
			__asm("str %[c2],[%[x]]"::[c2] "r" (c2), [x] "r" (x));
		}
		for(;x>ptr;x--){
			PUT8(x,c);
		}
	}
	else{
		for(int x = ptr + size; x > ptr; x--){
			PUT8(x,c);
		}
	}
	return (void *) ptr;
}

void *memcpy(int dest, int src, int size){
	/*for(int i = 0; i<size; i++){
		PUT8(dest,GET8(src));
		dest++;
		src++;
	}*/
	int dest2 = dest;
	if(size > 3){

		int x;
		dest += size;
		for(x = src + size; x > src + 3; x-=4){
			PUT32(dest,GET32(x));
			dest -=4;
		}
		for(;x>src;x--){
			PUT8(dest,GET8(x));
			dest--;
		}
	}
	else{
		dest += size;
		for(int i = src + size; i>src; i--){
			PUT8(dest,GET8(i));
			dest--;

		}
	}
	return (void *) dest2;
}
int strlen(const char* string){
	int length = 0;
	while(1){
		if(GET8((int)string++)==0){
			break;
		}
		length++;
	}
	return length;
}
