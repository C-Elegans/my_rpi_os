#include "string.h"
#include "uart.h"
void	*memchr(const void * ptr , int c, int size){

}
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
	
	int dest2 = dest;
	if(src < dest){
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
	}
	else{
		if(size>3){
			for(;dest<dest+size;dest+=4){
				PUT32(dest,GET32(src));
				src += 4;
			}
			for(;dest<dest+size;dest++){
				PUT8(dest,GET8(src));
				src++;
			}
		}
		else{
			for(;dest<dest+size;dest++){
				PUT8(dest,GET8(src));
				src++;
			}
		
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
char	*strcpy(char * dest, const char * src){
	for(int i=0;i<strlen(src);i++){
	dest[i] = src[i];
	}
	return dest;
}
