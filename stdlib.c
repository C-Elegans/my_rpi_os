#include "types.h"
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
char *itoa(int num, char *str, int radix){
	if (radix < 2 || radix > 16) return NULL;
	char newstr[(sizeof(int) * 8 + 1)];
	char *strptr = newstr;
	int count = 0;
	int negative = num < 0;
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
