ARMGNU ?= arm-none-eabi
AOPS = --warn
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -std=c99

all: cstdlib.bin

clean:
	rm *.o
	rm *.bin
	rm *.elf
	
start.o: start.s
	$(ARMGNU)-as start.s -o start.o 
timer.o: timer.s timer.h
	$(ARMGNU)-as timer.s -o timer.o

main.o: main.c
	$(ARMGNU)-gcc $(COPS) -c main.c -o main.o
video.o: video.c video.h
	$(ARMGNU)-gcc $(COPS) -c video.c -o video.o
uart.o: uart.c uart.h
	$(ARMGNU)-gcc $(COPS) -c uart.c -o uart.o
cstdlib.o: cstdlib.c
	$(ARMGNU)-gcc $(COPS) -c cstdlib.c -o cstdlib.o
cstdlib.elf: memmap start.o main.o uart.o timer.o video.o cstdlib.o mem.h
	$(ARMGNU)-ld start.o main.o uart.o timer.o video.o cstdlib.o -T memmap -o cstdlib.elf

cstdlib.bin: cstdlib.elf
	$(ARMGNU)-objcopy cstdlib.elf -O binary cstdlib.bin
