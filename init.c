#include <init.h>
#include <ktypes.h>
#include <console.h>

static ut64 idt[256];

void init () {
	ut64 gdt[3];

/* init the gdt */
	gdt[0] = 0LL;		//entry 0 gets ignored
	//codesegment ring 0
	set_gdt_entry (gdt, 1, 0, 0xfffff,
		generate_access_byte (false, false, true, true, 0, true),
		GDT_FLG_32BIT_4K);
	//datasegment ring 0
	set_gdt_entry (gdt, 2, 0, 0xfffff,
		generate_access_byte (true, false, false, true, 0, true),
		GDT_FLG_32BIT_4K);
	load_gdt (gdt, 3);	//3 entries
	load_idt (idt, register_interrupt_handlers (idt));
#if 1	
	outb (0x20, 0x13);	//no slave, but icw 4
	outb (0x80, 0x00);
	outb (0x21, 0x20);	//set hw interrupts to 0x20
	outb (0x80, 0x00);
	outb (0x21, 0x01);	//icw 4
	outb (0x80, 0x00);

	outb (0x21, 0x0d);	//only demask keyboard
#endif
	kputs ("lol");
	asm volatile ("sti"::);
	init_keyboard ();
#if 0
	asm volatile ("int 0x80");
	asm volatile ("int 0x80");
#endif
	while (true) {
		asm volatile ("hlt");
	}
}	
