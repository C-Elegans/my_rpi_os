ARMGNU ?=arm-none-eabi
AOPS = --warn
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -std=c99 -ggdb3

all: cstdlib.bin

clean:
	rm *.o
	rm *.bin
	rm *.elf
	
start.o: start.s
	$(ARMGNU)-as start.s -o start.o 
timer.o: timer.s timer.h
	$(ARMGNU)-as timer.s -o timer.o
interrupt.o: interrupt.s
	$(ARMGNU)-as interrupt.s -o interrupt.o
task_switch.o: task_switch.s
	$(ARMGNU)-as task_switch.s -o task_switch.o
main.o: main.c
	$(ARMGNU)-gcc $(COPS) -c main.c -o main.o
video.o: video.c video.h
	$(ARMGNU)-gcc $(COPS) -c video.c -o video.o
uart.o: uart.c uart.h
	$(ARMGNU)-gcc $(COPS) -c uart.c -o uart.o
string.o: string.c
	$(ARMGNU)-gcc $(COPS) -c string.c -o string.o
math.o: math.c
	$(ARMGNU)-gcc $(COPS) -c math.c -o math.o
maths.o: math.s
	$(ARMGNU)-as math.s -o maths.o
cstdlib.elf: memmap start.o main.o uart.o timer.o video.o string.o mem.h math.o maths.o interrupt.o task_switch.o
	$(ARMGNU)-ld start.o main.o uart.o timer.o video.o string.o math.o maths.o interrupt.o task_switch.o -T memmap -o cstdlib.elf

cstdlib.bin: cstdlib.elf
	$(ARMGNU)-objcopy cstdlib.elf -O binary cstdlib.bin
