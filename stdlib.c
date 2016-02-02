#include "types.h"
#include "stdlib.h"
int abs(int x){
	if (x & 1 << 31)
		return -x;
	return x;
}
long labs(long x){
	if (x < 0) return -x;
	return x;
}

char char_lut[] = "0123456789ABCDEF";


int atoi(const char *p){
	int ret = 0;

	while (*p) {
		if ('0' <= *p && *p <= '9') {
			ret *= 10;
			ret += *p - '0';
		}
		p++;
	}
	return ret;
}
long atol(const char *p){
	long ret = 0;

	while (*p) {
		if ('0' <= *p && *p <= '9') {
			ret *= 10;
			ret += *p - '0';
		}
		p++;
	}
	return ret;
}
char *internal_itoa(int num, char *str, int radix, int u){
	if (radix < 2 || radix > 16) return NULL;
	char newstr[(sizeof(int) * 8 + 1)];
	char *strptr = newstr;
	int count = 0;
	int negative = num < 0 && !u;
	num = (unsigned int)abs(num);
	while (num > 0) {
		*strptr = char_lut[num % (unsigned int)radix];
		num /= radix;
		strptr++;
		count++;
	}
	if (negative && radix == 10) {
		*strptr++ = '-';
		count++;
	}
	char *ptr = str;
	for (; count != 0; count--) {
		*ptr++ = *--strptr;
	}
	*ptr = 0;
	return str;
}
char* itoa(int num,char *str, int radix){
	return internal_itoa(num,str,radix,0);
}
char* utoa(unsigned int num,char *str, int radix){
	return internal_itoa(num,str,radix,1);
}
char *internal_ltoa(long num, char *str, int radix, int u){
	if (radix < 2 || radix > 16) return NULL;
	char newstr[(sizeof(long) * 8 + 1)];
	char *strptr = newstr;
	int count = 0;
	int negative = num < 0 && !u;
	num = (unsigned int)abs(num);
	while (num > 0) {
		*strptr = char_lut[num % (unsigned int)radix];
		num /= radix;
		strptr++;
		count++;
	}
	if (negative && radix == 10) {
		*strptr++ = '-';
		count++;
	}
	char *ptr = str;
	for (; count != 0; count--) {
		*ptr++ = *--strptr;
	}
	*ptr = 0;
	return str;
}
char* ltoa(long num,char *str, int radix){
	return internal_ltoa(num,str,radix,0);
}
char* ultoa(unsigned long num,char *str, int radix){
	return internal_itoa(num,str,radix,1);
}
static unsigned long int next = 1;

int rand(void) // RAND_MAX assumed to be 32767
{
	next = next * 1103515245 + 12345;
	return (unsigned int)(next/sizeof(int)) % RAND_MAX;
}

void srand(unsigned int seed)
{
	next = seed;
}
