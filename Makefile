ARMGNU ?=/Users/mnolan/bin/yagarto-4.7.2/bin/arm-none-eabi
AOPS = --warn
override CFLAGS+= -Wall -O3 -nostdlib -nostartfiles -ffreestanding -std=c99 -ggdb3
OBJS=start.o main.o uart.o timer.o video.o string.o mem.h math.o maths.o interrupt.o irq.o malloc.o task.o task_switch.o
all: cstdlib.bin
LDFLAGS=-flto

clean:
	rm *.o
	rm *.bin
	rm *.elf
	
%.o: %.s Makefile
	$(ARMGNU)-as $< -o $@
%.o: %.c Makefile
	$(ARMGNU)-gcc $(CFLAGS) -c $< -o $@	

cstdlib.elf: memmap $(OBJS) Makefile
	$(ARMGNU)-gcc $(LDFLAGS) $(OBJS) -T memmap -o cstdlib.elf $(CFLAGS)
	$(ARMGNU)-objdump -d cstdlib.elf > dump.text

cstdlib.bin: cstdlib.elf Makefile
	$(ARMGNU)-objcopy cstdlib.elf -O binary cstdlib.bin
	$(ARMGNU)-objcopy --only-keep-debug cstdlib.elf cstdlib.sym
	
qemu: cstdlib.elf
	qemu-system-arm -kernel cstdlib.elf  -cpu arm1176 -m 256 -M versatilepb -S -s
