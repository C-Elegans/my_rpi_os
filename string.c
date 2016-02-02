#include "string.h"
#include "uart.h"
#include "types.h"
void *memchr(const void *ptr, int c, int size){
	return NULL;
}
void *memset(void *ptr, const void *c, int size){
	if (size > 3) {
		void *c2 = (void *)((int)c | ((int)c << 8) | ((int)c << 16) | ((int)c << 24));
		void *x;
		for (x = ptr + size; x > ptr + 3; x -= 4) {
			//PUT32(x,c2);
			__asm("str %[c2],[%[x]]" ::[c2] "r" (c2), [x] "r" (x));
		}
		for (; x > (void *)ptr; x--) {
			PUT8((int)x, (int)c);
		}
	} else {
		for (void *x = ptr + size; x > ptr; x--) {
			PUT8((int)x, (int)c);
		}
	}
	return (void *)ptr;
}
void *fast_memset(int ptr, int c, int size){
	if (size > 3) {
		int c2 = (c | (c << 8) | (c << 16) | (c << 24));
		int x;
		for (x = ptr + size; x > ptr + 3; x -= 4) {
			//PUT32(x,c2);
			__asm("str %[c2],[%[x]]" ::[c2] "r" (c2), [x] "r" (x));
		}
		for (; x > ptr; x--) {
			PUT8(x, c);
		}
	} else {
		for (int x = ptr + size; x > ptr; x--) {
			PUT8(x, c);
		}
	}
	return (void *)ptr;
}

void *memcpy(void *dest, void *src, int size){
	void *dest2 = dest;

	if (src < dest) {
		if (size > 3) {
			void *x;
			dest += size;
			for (x = src + size; x > src + 3; x -= 4) {
				PUT32((int)dest, (int)GET32((int)x));
				dest -= 4;
			}
			for (; x > src; x--) {
				PUT8((int)dest, GET8((int)x));
				dest--;
			}
		} else {
			dest += size;
			for (void *i = src + size; i > src; i--) {
				PUT8((int)dest, GET8((int)i));
				dest--;
			}
		}
	} else {
		if (size > 3) {
			for (; dest < dest + size; dest += 4) {
				PUT32((int)dest, GET32((int)src));
				src += 4;
			}
			for (; dest < dest + size; dest++) {
				PUT8((int)dest, GET8((int)src));
				src++;
			}
		} else {
			for (; dest < dest + size; dest++) {
				PUT8((int)dest, GET8((int)src));
				src++;
			}
		}
	}
	return (void *)dest2;
}
int strlen(const char *string){
	int length = 0;

	while (1) {
		if (*(string++) == 0)
			break;
		length++;
	}
	return length;
}
char *strcpy(char *dest, const char *src){
	for (int i = 0; i < strlen(src); i++) {
		dest[i] = src[i];
	}
	return dest;
}
char *strcat(char *dest, const char *src){
	int len = strlen(dest);

	dest += len;
	strcpy(dest, src);
	return dest;
}
char *strchr(const char *str, int c){
	char chr = (char)c;

	do
		if (*str == chr)
			return (char *)str;
	while (*(str++));
	return NULL;
}
int strcmp(const char *p1, const char *p2){
	while (*p1) {
		if (p2 == NULL) return 1;
		if (*p1 > *p2) return 1;
		if (*p1 < *p2) return -1;
		p1++;
		p2++;
	}
	if (p1 == NULL) return -1;
	return 0;
}
char *strstr(const char * str , const char * pattern){
	while(*str){
		char* begin = (char*)str;
		const char* p2= pattern;
		while(*str && *p2 && *str == *p2){
			str++;
			p2++;
		}
		if(! *p2)return begin;
		str = begin + 1;
	}
	return NULL;
	
}
char* strtok(char* source , const char *find ){
	static char* str;
	if(source != NULL) str = source;
	if(str == NULL) return NULL;
	int len = strlen(find);
	char* match = strstr(str,find);
	if(match == NULL){
		char* strprev = str;
		str = NULL;
		return strprev;
	}
	*match = 0;
	char* ret = str;
	str = match + len;
	return ret;
}
