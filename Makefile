OBJS = init.o gdt.o idt.o console.o keyboard.o start.o

CC = gcc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -masm=intel -Wall -g -fno-stack-protector -nostdinc -I include/
LDFLAGS = -melf_i386 -Tkernel.ld

boot.iso: img/kernel
	grub-mkrescue -o boot.iso img/

img/kernel: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o img/kernel

gdt.o:
	$(CC) $(CFLAGS) -c -o gdt.o gdt.c

idt.o:
	$(CC) $(CFLAGS) -c -o idt.o idt.c

console.o:
	$(CC) $(CFLAGS) -c -o console.o console.c

keyboard.o:
	$(CC) $(CFLAGS) -c -o keyboard.o keyboard.c

init.o:
	$(CC) $(CFLAGS) -c -o init.o init.c

%.o: %.S
	$(CC) $(ASFLAGS) -c -o start.o start.S

clean:
	rm $(OBJS) boot.iso img/kernel

.PHONY: clean
