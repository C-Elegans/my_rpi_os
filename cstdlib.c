#include "cstdlib.h"
//#include "uart.h"

void memset(int ptr, int c, int size){
	
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
}

void memcpy(int dest, int src, int size){
	for(int i = 0; i<size; i++){
		PUT8(dest,GET8(src));
		dest++;
		src++;
	}
}
