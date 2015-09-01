ARMGNU ?=arm-none-eabi
AOPS = --warn
COPS = -Wall -O0 -nostdlib -nostartfiles -ffreestanding -std=c99 -ggdb3
OBJS=start.o main.o uart.o timer.o video.o string.o mem.h math.o maths.o interrupt.o 
all: cstdlib.bin
LDFLAGS=

clean:
	rm *.o
	rm *.bin
	rm *.elf
	
%.o: %.s
	$(ARMGNU)-as $< -o $@
%.o: %.c
	$(ARMGNU)-gcc $(COPS) -c $< -o $@	

cstdlib.elf: memmap $(OBJS)
	$(ARMGNU)-gcc $(LDFLAGS) $(OBJS) -T memmap -o cstdlib.elf $(COPS)
	$(ARMGNU)-objdump -d cstdlib.elf > dump.text

cstdlib.bin: cstdlib.elf
	$(ARMGNU)-objcopy cstdlib.elf -O binary cstdlib.bin
	$(ARMGNU)-objcopy --only-keep-debug cstdlib.elf cstdlib.sym
	
