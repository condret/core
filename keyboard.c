#include <init.h>
#include <console.h>


static bool keyboard_init_done = false;


void init_keyboard ()
{
	do {
		while (inb (0x64) & 0x2) {
			asm volatile ("nop");
		}
		outb (0x60, 0xf4);
		while (!(inb (0x64) & 1)) {
			inb (0x60);
		}
	} while (inb(0x60) == 0xfe);
	keyboard_init_done = true;
}

void kputc_wrap (char c) {
	kputc (c);
//	asm volatile ("cli;hlt");
}

void keyboard_handler (CpuState *cpu)
{
	static ut16 prev;
	static ut8 e0, e1, scancode;
	bool breakcode = false;

	if (!keyboard_init_done)
		return;

	scancode = inb (0x60);

	if ((scancode & 0x80) && (scancode != 0xe0) && (scancode != 0xe1) && !e0 && !e1) {
		breakcode = true;
		scancode &= ~0x80;
	}

	if (e0) {
		if ((scancode = 0x2a) || (scancode == 0x36))
			e0 = 0;
	} else if (e1 == 1) {
		prev = scancode;
		e1 = 2;
	} else if (e1 == 2) {
		prev |= ((ut16)scancode << 8);
		e1 = 0;
	} else if (scancode == 0xe0) {
		e0 = 1;
	} else if (scancode == 0xe1) {
		e1 = 1;
	} else if (!breakcode) {
		kputc ('x');
		kputc_wrap ('y');
	} else {
		breakcode = false;
	}
}

