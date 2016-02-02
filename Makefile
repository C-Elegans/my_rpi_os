ARMGNU ?=/Users/mnolan/bin/yagarto-4.7.2/bin/arm-none-eabi
AOPS = --warn
override CFLAGS+= -Wall -Os -nostdlib -nostartfiles -ffreestanding -std=c99 -ggdb3 -flto 
OBJS=start.o main.o uart.o timer.o video.o string.o mem.h math.o maths.o stdlib.o interrupt.o irq.o malloc.o task.o task_switch.o

all: cstdlib.bin
LDFLAGS=-flto -Os -lgcc

clean:
	rm *.o
	rm *.bin
	rm *.elf
math.o:math.c
	$(ARMGNU)-gcc -mfpu=vfp3 $(CFLAGS) -fno-lto -c math.c -o math.o
%.o: %.s Makefile
	$(ARMGNU)-as -mfpu=vfp3 $< -o $@
%.o: %.c Makefile

	$(ARMGNU)-gcc -mfpu=vfp3 $(CFLAGS) -c $< -o $@	

cstdlib.elf: memmap $(OBJS) Makefile
	$(ARMGNU)-gcc $(LDFLAGS) $(OBJS) -T memmap -o cstdlib.elf $(CFLAGS)
	$(ARMGNU)-objdump -d cstdlib.elf > dump.text

cstdlib.bin: cstdlib.elf Makefile
	$(ARMGNU)-objcopy cstdlib.elf -O binary cstdlib.bin
	$(ARMGNU)-objcopy --only-keep-debug cstdlib.elf cstdlib.sym
	
qemu: cstdlib.elf
	qemu-system-arm -kernel cstdlib.elf  -cpu arm1176 -m 256 -M versatilepb -S -s

uncrustify:
	uncrustify -c uncrustify.cfg --replace --no-backup *.c
	uncrustify -c uncrustify.cfg --replace --no-backup *.h