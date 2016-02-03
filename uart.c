#include "uart.h"
#include "math.h"
#include "timer.h"
typedef enum { false, true } bool;
void uart_init(){
	unsigned int ra;

	PUT32(AUX_ENABLES, 1);
	PUT32(AUX_MU_IER_REG, 0);
	PUT32(AUX_MU_CNTL_REG, 0);
	PUT32(AUX_MU_LCR_REG, 3);
	PUT32(AUX_MU_MCR_REG, 0);
	PUT32(AUX_MU_IER_REG, 0);
	PUT32(AUX_MU_IIR_REG, 0xC6);
	PUT32(AUX_MU_BAUD_REG, 270);

	ra = GET32(GPFSEL1);
	ra &= ~(7 << 12);       //gpio14
	ra |= 2 << 12;          //alt5
	PUT32(GPFSEL1, ra);

	PUT32(GPPUD, 0);
	for (ra = 0; ra < 150; ra++) {
		dummy(ra);
	}
	PUT32(GPPUDCLK0, (1 << 14));
	for (ra = 0; ra < 150; ra++) {
		dummy(ra);
	}
	PUT32(GPPUDCLK0, 0);

	PUT32(AUX_MU_CNTL_REG, 2);
}
void putc(char c){
#ifndef QEMU
	while (1)
		if (GET32(AUX_MU_LSR_REG) & 0x20) break;
	PUT32(AUX_MU_IO_REG, c);
#endif
}

void puts(char str[]){
	int i = 0;

	while (str[i] != 0) {
		putc(str[i]);
		i++;
	}
}
void uart_putint(unsigned int input){
	//char buf[15];
	int div = 1000000000;
	int test;

	for (int i = 0; i < 10; i++) {
		test = input / div;
		test = (unsigned int)test % (unsigned int)10;
		//hexstring(div);
		putc(test + '0');


		div = div / 10;
	}
	puts("\r\n");
}
void hexstrings(unsigned int d){
	//unsigned int ra;
	unsigned int rb;
	unsigned int rc;

	rb = 32;
	while (1) {
		rb -= 4;
		rc = (d >> rb) & 0xF;
		if (rc > 9) rc += 0x37; else rc += 0x30;
		putc(rc);
		if (rb == 0) break;
	}
	putc(0x20);
}
//------------------------------------------------------------------------
void hexstring(unsigned int d){
	hexstrings(d);
	putc(0x0D);
	putc(0x0A);
}
void uart_putfloat(float f){
}
