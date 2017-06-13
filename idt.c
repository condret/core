#include <init.h>

void set_idt_entry (ut64 *idt, ut16 i, ut32 offset, ut16 cs, interrupt_type_t it, ut8 priv, bool p)
{
	idt[i] = (offset & 0xffff);
	idt[i] |= (cs << 16);
	idt[i] |= ((ut64)it << 40);
	idt[i] |= (1ULL << 43);			//allways 32-bit mode
	idt[i] |= ((ut64)(priv & 3) << 45);
	idt[i] |= ((ut64)!!p << 47);
	idt[i] |= ((ut64)(offset & 0xffff0000) << 32);
}


void load_idt (ut64 *idt, ut16 idt_sz)
{
	IdtPointer idtp = {
		.limit = (idt_sz * 8) - 1,
		.pointer = idt,
	};
	asm volatile ( "lidt %0" :: "m" (idtp));
}

void outb(ut16 port, ut8 data)
{
	asm volatile ("outb %0, %1" : : "Nd" (port), "a" (data));
}

ut8 inb(ut16 port)
{
	ut8 ret;
	asm volatile ("inb %0, %1" : "=a" (ret) : "Nd" (port));
	return ret;
}

void default_interrupt_handler (CpuState *cpu)
{
	if (cpu->intr == 33)
		keyboard_handler (cpu);
	if ((cpu->intr >= 0x20) && (cpu->intr < 0x28))
		outb (0x20, 0x20);	//send EOI to master-pic
}

ut16 register_interrupt_handlers (ut64 *idt)
{
	ut16 i;

	//Hacking around gcc
	asm volatile goto ("":::: handler0, handler1, handler2, handler3, handler4, handler5,
		handler6, handler7, handler8, handler9, handler10, handler11, handler12,
		handler13, handler14, handler15, handler16, handler17, handler18, handler33,
		handler34, handler35, handler36, handler37, handler38, handler39, handler40);
	asm volatile goto ("":::: handler41, handler42, handler43, handler44, handler45, handler46, handler47,
		handler48, handler49, handler50, handler51, handler52, handler53, handler54,
		handler55, handler56, handler57, handler58, handler59, handler60, handler61,
		handler62, handler63, handler64, handler65, handler66, handler67, handler68);
	asm volatile goto ("":::: handler69, handler70, handler71, handler72, handler73, handler74, handler75,
		handler76, handler77, handler78, handler79, handler80, handler81, handler82,
		handler83, handler84, handler85, handler86, handler87, handler88, handler89,
		handler90, handler91, handler92, handler93, handler94, handler95, handler96);
	asm volatile goto ("":::: handler97, handler98, handler99, handler100, handler101, handler102, handler103,
		handler104, handler105, handler106, handler107, handler108, handler109, handler110,
		handler111, handler112, handler113, handler114, handler115, handler116, handler117,
		handler118, handler119, handler120, handler121, handler122, handler123, handler124);
	asm volatile goto ("":::: handler125, handler126, handler127, handler128, handler129, handler130, handler131,
		handler132, handler133, handler134, handler135, handler136, handler137, handler138,
		handler139, handler140, handler141, handler142, handler143, handler144, handler145,
		handler146, handler147, handler148, handler149, handler150, handler151, handler152);
	asm volatile goto ("":::: handler153, handler154, handler155, handler156, handler157, handler158, handler159,
		handler160, handler161, handler162, handler163, handler164, handler165, handler166,
		handler167, handler168, handler169, handler170, handler171, handler172, handler173,
		handler174, handler175, handler176, handler177, handler178, handler179, handler180);
	asm volatile goto ("":::: handler181, handler182, handler183, handler184, handler185, handler186, handler187,
		handler188, handler189, handler190, handler191, handler192, handler193, handler194,
		handler195, handler196, handler197, handler198, handler199, handler200, handler201,
		handler202, handler203, handler204, handler205, handler206, handler207, handler208);
	asm volatile goto ("":::: handler209, handler210, handler211, handler212, handler213, handler214, handler215,
		handler216, handler217, handler218, handler219, handler220, handler221, handler222,
		handler223, handler224, handler225, handler226, handler227, handler228, handler229,
		handler230, handler231, handler232, handler233, handler234, handler235, handler236);
	asm volatile goto ("":::: handler237, handler238, handler239, handler240, handler241, handler242, handler243,
		handler244, handler245, handler246, handler247, handler248, handler249, handler250,
		handler251, handler252, handler253, handler254, handler255);

	set_idt_entry (idt, 0, (ut32)(&&handler0), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 1, (ut32)(&&handler1), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 2, (ut32)(&&handler2), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 3, (ut32)(&&handler3), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 4, (ut32)(&&handler4), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 5, (ut32)(&&handler5), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 6, (ut32)(&&handler6), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 7, (ut32)(&&handler7), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 8, (ut32)(&&handler8), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 9, (ut32)(&&handler9), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 10, (ut32)(&&handler10), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 11, (ut32)(&&handler11), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 12, (ut32)(&&handler12), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 13, (ut32)(&&handler13), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 14, (ut32)(&&handler14), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 15, (ut32)(&&handler15), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 16, (ut32)(&&handler16), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 17, (ut32)(&&handler17), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 18, (ut32)(&&handler18), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	for (i = 19; i < 33; i++)
		idt[i] = 0LL;
	set_idt_entry (idt, 33, (ut32)(&&handler33), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 34, (ut32)(&&handler34), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 35, (ut32)(&&handler35), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 36, (ut32)(&&handler36), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 37, (ut32)(&&handler37), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 38, (ut32)(&&handler38), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 39, (ut32)(&&handler39), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 40, (ut32)(&&handler40), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 41, (ut32)(&&handler41), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 42, (ut32)(&&handler42), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 43, (ut32)(&&handler43), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 44, (ut32)(&&handler44), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 45, (ut32)(&&handler45), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 46, (ut32)(&&handler46), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 47, (ut32)(&&handler47), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 48, (ut32)(&&handler48), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 49, (ut32)(&&handler49), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 50, (ut32)(&&handler50), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 51, (ut32)(&&handler51), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 52, (ut32)(&&handler52), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 53, (ut32)(&&handler53), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 54, (ut32)(&&handler54), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 55, (ut32)(&&handler55), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 56, (ut32)(&&handler56), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 57, (ut32)(&&handler57), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 58, (ut32)(&&handler58), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 59, (ut32)(&&handler59), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 60, (ut32)(&&handler60), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 61, (ut32)(&&handler61), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 62, (ut32)(&&handler62), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 63, (ut32)(&&handler63), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 64, (ut32)(&&handler64), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 65, (ut32)(&&handler65), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 66, (ut32)(&&handler66), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 67, (ut32)(&&handler67), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 68, (ut32)(&&handler68), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 69, (ut32)(&&handler69), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 70, (ut32)(&&handler70), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 71, (ut32)(&&handler71), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 72, (ut32)(&&handler72), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 73, (ut32)(&&handler73), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 74, (ut32)(&&handler74), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 75, (ut32)(&&handler75), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 76, (ut32)(&&handler76), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 77, (ut32)(&&handler77), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 78, (ut32)(&&handler78), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 79, (ut32)(&&handler79), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 80, (ut32)(&&handler80), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 81, (ut32)(&&handler81), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 82, (ut32)(&&handler82), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 83, (ut32)(&&handler83), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 84, (ut32)(&&handler84), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 85, (ut32)(&&handler85), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 86, (ut32)(&&handler86), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 87, (ut32)(&&handler87), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 88, (ut32)(&&handler88), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 89, (ut32)(&&handler89), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 90, (ut32)(&&handler90), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 91, (ut32)(&&handler91), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 92, (ut32)(&&handler92), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 93, (ut32)(&&handler93), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 94, (ut32)(&&handler94), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 95, (ut32)(&&handler95), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 96, (ut32)(&&handler96), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 97, (ut32)(&&handler97), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 98, (ut32)(&&handler98), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 99, (ut32)(&&handler99), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 100, (ut32)(&&handler100), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 101, (ut32)(&&handler101), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 102, (ut32)(&&handler102), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 103, (ut32)(&&handler103), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 104, (ut32)(&&handler104), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 105, (ut32)(&&handler105), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 106, (ut32)(&&handler106), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 107, (ut32)(&&handler107), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 108, (ut32)(&&handler108), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 109, (ut32)(&&handler109), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 110, (ut32)(&&handler110), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 111, (ut32)(&&handler111), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 112, (ut32)(&&handler112), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 113, (ut32)(&&handler113), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 114, (ut32)(&&handler114), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 115, (ut32)(&&handler115), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 116, (ut32)(&&handler116), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 117, (ut32)(&&handler117), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 118, (ut32)(&&handler118), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 119, (ut32)(&&handler119), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 120, (ut32)(&&handler120), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 121, (ut32)(&&handler121), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 122, (ut32)(&&handler122), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 123, (ut32)(&&handler123), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 124, (ut32)(&&handler124), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 125, (ut32)(&&handler125), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 126, (ut32)(&&handler126), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 127, (ut32)(&&handler127), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 128, (ut32)(&&handler128), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 129, (ut32)(&&handler129), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 130, (ut32)(&&handler130), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 131, (ut32)(&&handler131), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 132, (ut32)(&&handler132), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 133, (ut32)(&&handler133), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 134, (ut32)(&&handler134), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 135, (ut32)(&&handler135), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 136, (ut32)(&&handler136), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 137, (ut32)(&&handler137), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 138, (ut32)(&&handler138), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 139, (ut32)(&&handler139), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 140, (ut32)(&&handler140), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 141, (ut32)(&&handler141), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 142, (ut32)(&&handler142), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 143, (ut32)(&&handler143), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 144, (ut32)(&&handler144), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 145, (ut32)(&&handler145), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 146, (ut32)(&&handler146), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 147, (ut32)(&&handler147), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 148, (ut32)(&&handler148), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 149, (ut32)(&&handler149), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 150, (ut32)(&&handler150), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 151, (ut32)(&&handler151), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 152, (ut32)(&&handler152), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 153, (ut32)(&&handler153), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 154, (ut32)(&&handler154), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 155, (ut32)(&&handler155), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 156, (ut32)(&&handler156), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 157, (ut32)(&&handler157), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 158, (ut32)(&&handler158), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 159, (ut32)(&&handler159), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 160, (ut32)(&&handler160), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 161, (ut32)(&&handler161), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 162, (ut32)(&&handler162), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 163, (ut32)(&&handler163), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 164, (ut32)(&&handler164), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 165, (ut32)(&&handler165), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 166, (ut32)(&&handler166), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 167, (ut32)(&&handler167), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 168, (ut32)(&&handler168), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 169, (ut32)(&&handler169), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 170, (ut32)(&&handler170), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 171, (ut32)(&&handler171), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 172, (ut32)(&&handler172), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 173, (ut32)(&&handler173), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 174, (ut32)(&&handler174), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 175, (ut32)(&&handler175), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 176, (ut32)(&&handler176), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 177, (ut32)(&&handler177), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 178, (ut32)(&&handler178), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 179, (ut32)(&&handler179), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 180, (ut32)(&&handler180), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 181, (ut32)(&&handler181), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 182, (ut32)(&&handler182), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 183, (ut32)(&&handler183), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 184, (ut32)(&&handler184), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 185, (ut32)(&&handler185), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 186, (ut32)(&&handler186), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 187, (ut32)(&&handler187), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 188, (ut32)(&&handler188), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 189, (ut32)(&&handler189), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 190, (ut32)(&&handler190), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 191, (ut32)(&&handler191), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 192, (ut32)(&&handler192), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 193, (ut32)(&&handler193), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 194, (ut32)(&&handler194), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 195, (ut32)(&&handler195), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 196, (ut32)(&&handler196), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 197, (ut32)(&&handler197), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 198, (ut32)(&&handler198), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 199, (ut32)(&&handler199), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 200, (ut32)(&&handler200), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 201, (ut32)(&&handler201), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 202, (ut32)(&&handler202), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 203, (ut32)(&&handler203), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 204, (ut32)(&&handler204), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 205, (ut32)(&&handler205), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 206, (ut32)(&&handler206), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 207, (ut32)(&&handler207), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 208, (ut32)(&&handler208), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 209, (ut32)(&&handler209), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 210, (ut32)(&&handler210), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 211, (ut32)(&&handler211), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 212, (ut32)(&&handler212), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 213, (ut32)(&&handler213), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 214, (ut32)(&&handler214), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 215, (ut32)(&&handler215), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 216, (ut32)(&&handler216), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 217, (ut32)(&&handler217), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 218, (ut32)(&&handler218), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 219, (ut32)(&&handler219), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 220, (ut32)(&&handler220), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 221, (ut32)(&&handler221), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 222, (ut32)(&&handler222), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 223, (ut32)(&&handler223), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 224, (ut32)(&&handler224), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 225, (ut32)(&&handler225), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 226, (ut32)(&&handler226), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 227, (ut32)(&&handler227), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 228, (ut32)(&&handler228), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 229, (ut32)(&&handler229), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 230, (ut32)(&&handler230), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 231, (ut32)(&&handler231), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 232, (ut32)(&&handler232), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 233, (ut32)(&&handler233), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 234, (ut32)(&&handler234), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 235, (ut32)(&&handler235), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 236, (ut32)(&&handler236), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 237, (ut32)(&&handler237), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 238, (ut32)(&&handler238), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 239, (ut32)(&&handler239), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 240, (ut32)(&&handler240), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 241, (ut32)(&&handler241), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 242, (ut32)(&&handler242), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 243, (ut32)(&&handler243), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 244, (ut32)(&&handler244), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 245, (ut32)(&&handler245), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 246, (ut32)(&&handler246), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 247, (ut32)(&&handler247), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 248, (ut32)(&&handler248), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 249, (ut32)(&&handler249), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 250, (ut32)(&&handler250), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 251, (ut32)(&&handler251), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 252, (ut32)(&&handler252), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 253, (ut32)(&&handler253), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 254, (ut32)(&&handler254), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	set_idt_entry (idt, 255, (ut32)(&&handler255), 0x8, INTERRUPT_TYPE_INTERRUPT_GATE, 0, true);
	goto beach;
handler0:
	asm volatile (
		"push 0\n"
		"push 0\n"
		::);
	goto d_handler;
handler1:
	asm volatile (
		"push 0\n"
		"push 1\n"
		::);
	goto d_handler;
handler2:
	asm volatile (
		"push 0\n"
		"push 2\n"
		::);
	goto d_handler;
handler3:
	asm volatile (
		"push 0\n"
		"push 3\n"
		::);
	goto d_handler;
handler4:
	asm volatile (
		"push 0\n"
		"push 4\n"
		::);
	goto d_handler;
handler5:
	asm volatile (
		"push 0\n"
		"push 5\n"
		::);
	goto d_handler;
handler6:
	asm volatile (
		"push 0\n"
		"push 6\n"
		::);
	goto d_handler;
handler7:
	asm volatile (
		"push 0\n"
		"push 1\n"
		::);
	goto d_handler;
handler8:
	asm volatile ( "push 8\n" ::);
	goto d_handler;
handler9:
	asm volatile (
		"push 0\n"
		"push 9\n"
		::);
	goto d_handler;
handler10:
	asm volatile ( "push 10\n" ::);
	goto d_handler;
handler11:
	asm volatile ( "push 11\n" ::);
	goto d_handler;
handler12:
	asm volatile ( "push 12\n" ::);
	goto d_handler;
handler13:
	asm volatile ( "push 13\n" ::);
	goto d_handler;
handler14:
	asm volatile ( "push 14\n" ::);
	goto d_handler;
handler15:
	asm volatile (
		"push 0\n"
		"push 15\n"
		::);
	goto d_handler;
handler16:
	asm volatile (
		"push 0\n"
		"push 16\n"
		::);
	goto d_handler;
handler17:
	asm volatile ( "push 17\n" ::);
	goto d_handler;
handler18:
	asm volatile (
		"push 0\n"
		"push 18\n"
		::);
	goto d_handler;
handler33:		//keyboard
	asm volatile (
		"push 0\n"
		"push 33\n"
		::);
	goto d_handler;
handler34:
	asm volatile (
		"push 0\n"
		"push 34\n"
		::);
	goto d_handler;
handler35:
	asm volatile (
		"push 0\n"
		"push 35\n"
		::);
	goto d_handler;
handler36:
	asm volatile (
		"push 0\n"
		"push 36\n"
		::);
	goto d_handler;
handler37:
	asm volatile (
		"push 0\n"
		"push 37\n"
		::);
	goto d_handler;
handler38:
	asm volatile (
		"push 0\n"
		"push 38\n"
		::);
	goto d_handler;
handler39:
	asm volatile (
		"push 0\n"
		"push 39\n"
		::);
	goto d_handler;
handler40:
	asm volatile (
		"push 0\n"
		"push 40\n"
		::);
	goto d_handler;
handler41:
	asm volatile (
		"push 0\n"
		"push 41\n"
		::);
	goto d_handler;
handler42:
	asm volatile (
		"push 0\n"
		"push 42\n"
		::);
	goto d_handler;
handler43:
	asm volatile (
		"push 0\n"
		"push 43\n"
		::);
	goto d_handler;
handler44:
	asm volatile (
		"push 0\n"
		"push 44\n"
		::);
	goto d_handler;
handler45:
	asm volatile (
		"push 0\n"
		"push 45\n"
		::);
	goto d_handler;
handler46:
	asm volatile (
		"push 0\n"
		"push 46\n"
		::);
	goto d_handler;
handler47:
	asm volatile (
		"push 0\n"
		"push 47\n"
		::);
	goto d_handler;
handler48:
	asm volatile (
		"push 0\n"
		"push 48\n"
		::);
	goto d_handler;
handler49:
	asm volatile (
		"push 0\n"
		"push 49\n"
		::);
	goto d_handler;
handler50:
	asm volatile (
		"push 0\n"
		"push 50\n"
		::);
	goto d_handler;
handler51:
	asm volatile (
		"push 0\n"
		"push 51\n"
		::);
	goto d_handler;
handler52:
	asm volatile (
		"push 0\n"
		"push 52\n"
		::);
	goto d_handler;
handler53:
	asm volatile (
		"push 0\n"
		"push 53\n"
		::);
	goto d_handler;
handler54:
	asm volatile (
		"push 0\n"
		"push 54\n"
		::);
	goto d_handler;
handler55:
	asm volatile (
		"push 0\n"
		"push 55\n"
		::);
	goto d_handler;
handler56:
	asm volatile (
		"push 0\n"
		"push 56\n"
		::);
	goto d_handler;
handler57:
	asm volatile (
		"push 0\n"
		"push 57\n"
		::);
	goto d_handler;
handler58:
	asm volatile (
		"push 0\n"
		"push 58\n"
		::);
	goto d_handler;
handler59:
	asm volatile (
		"push 0\n"
		"push 59\n"
		::);
	goto d_handler;
handler60:
	asm volatile (
		"push 0\n"
		"push 60\n"
		::);
	goto d_handler;
handler61:
	asm volatile (
		"push 0\n"
		"push 61\n"
		::);
	goto d_handler;
handler62:
	asm volatile (
		"push 0\n"
		"push 62\n"
		::);
	goto d_handler;
handler63:
	asm volatile (
		"push 0\n"
		"push 63\n"
		::);
	goto d_handler;
handler64:
	asm volatile (
		"push 0\n"
		"push 64\n"
		::);
	goto d_handler;
handler65:
	asm volatile (
		"push 0\n"
		"push 65\n"
		::);
	goto d_handler;
handler66:
	asm volatile (
		"push 0\n"
		"push 66\n"
		::);
	goto d_handler;
handler67:
	asm volatile (
		"push 0\n"
		"push 67\n"
		::);
	goto d_handler;
handler68:
	asm volatile (
		"push 0\n"
		"push 68\n"
		::);
	goto d_handler;
handler69:
	asm volatile (
		"push 0\n"
		"push 69\n"
		::);
	goto d_handler;
handler70:
	asm volatile (
		"push 0\n"
		"push 70\n"
		::);
	goto d_handler;
handler71:
	asm volatile (
		"push 0\n"
		"push 71\n"
		::);
	goto d_handler;
handler72:
	asm volatile (
		"push 0\n"
		"push 72\n"
		::);
	goto d_handler;
handler73:
	asm volatile (
		"push 0\n"
		"push 73\n"
		::);
	goto d_handler;
handler74:
	asm volatile (
		"push 0\n"
		"push 74\n"
		::);
	goto d_handler;
handler75:
	asm volatile (
		"push 0\n"
		"push 75\n"
		::);
	goto d_handler;
handler76:
	asm volatile (
		"push 0\n"
		"push 76\n"
		::);
	goto d_handler;
handler77:
	asm volatile (
		"push 0\n"
		"push 77\n"
		::);
	goto d_handler;
handler78:
	asm volatile (
		"push 0\n"
		"push 78\n"
		::);
	goto d_handler;
handler79:
	asm volatile (
		"push 0\n"
		"push 79\n"
		::);
	goto d_handler;
handler80:
	asm volatile (
		"push 0\n"
		"push 80\n"
		::);
	goto d_handler;
handler81:
	asm volatile (
		"push 0\n"
		"push 81\n"
		::);
	goto d_handler;
handler82:
	asm volatile (
		"push 0\n"
		"push 82\n"
		::);
	goto d_handler;
handler83:
	asm volatile (
		"push 0\n"
		"push 83\n"
		::);
	goto d_handler;
handler84:
	asm volatile (
		"push 0\n"
		"push 84\n"
		::);
	goto d_handler;
handler85:
	asm volatile (
		"push 0\n"
		"push 85\n"
		::);
	goto d_handler;
handler86:
	asm volatile (
		"push 0\n"
		"push 86\n"
		::);
	goto d_handler;
handler87:
	asm volatile (
		"push 0\n"
		"push 87\n"
		::);
	goto d_handler;
handler88:
	asm volatile (
		"push 0\n"
		"push 88\n"
		::);
	goto d_handler;
handler89:
	asm volatile (
		"push 0\n"
		"push 89\n"
		::);
	goto d_handler;
handler90:
	asm volatile (
		"push 0\n"
		"push 90\n"
		::);
	goto d_handler;
handler91:
	asm volatile (
		"push 0\n"
		"push 91\n"
		::);
	goto d_handler;
handler92:
	asm volatile (
		"push 0\n"
		"push 92\n"
		::);
	goto d_handler;
handler93:
	asm volatile (
		"push 0\n"
		"push 93\n"
		::);
	goto d_handler;
handler94:
	asm volatile (
		"push 0\n"
		"push 94\n"
		::);
	goto d_handler;
handler95:
	asm volatile (
		"push 0\n"
		"push 95\n"
		::);
	goto d_handler;
handler96:
	asm volatile (
		"push 0\n"
		"push 96\n"
		::);
	goto d_handler;
handler97:
	asm volatile (
		"push 0\n"
		"push 97\n"
		::);
	goto d_handler;
handler98:
	asm volatile (
		"push 0\n"
		"push 98\n"
		::);
	goto d_handler;
handler99:
	asm volatile (
		"push 0\n"
		"push 99\n"
		::);
	goto d_handler;
handler100:
	asm volatile (
		"push 0\n"
		"push 100\n"
		::);
	goto d_handler;
handler101:
	asm volatile (
		"push 0\n"
		"push 101\n"
		::);
	goto d_handler;
handler102:
	asm volatile (
		"push 0\n"
		"push 102\n"
		::);
	goto d_handler;
handler103:
	asm volatile (
		"push 0\n"
		"push 103\n"
		::);
	goto d_handler;
handler104:
	asm volatile (
		"push 0\n"
		"push 104\n"
		::);
	goto d_handler;
handler105:
	asm volatile (
		"push 0\n"
		"push 105\n"
		::);
	goto d_handler;
handler106:
	asm volatile (
		"push 0\n"
		"push 106\n"
		::);
	goto d_handler;
handler107:
	asm volatile (
		"push 0\n"
		"push 107\n"
		::);
	goto d_handler;
handler108:
	asm volatile (
		"push 0\n"
		"push 108\n"
		::);
	goto d_handler;
handler109:
	asm volatile (
		"push 0\n"
		"push 109\n"
		::);
	goto d_handler;
handler110:
	asm volatile (
		"push 0\n"
		"push 110\n"
		::);
	goto d_handler;
handler111:
	asm volatile (
		"push 0\n"
		"push 111\n"
		::);
	goto d_handler;
handler112:
	asm volatile (
		"push 0\n"
		"push 112\n"
		::);
	goto d_handler;
handler113:
	asm volatile (
		"push 0\n"
		"push 113\n"
		::);
	goto d_handler;
handler114:
	asm volatile (
		"push 0\n"
		"push 114\n"
		::);
	goto d_handler;
handler115:
	asm volatile (
		"push 0\n"
		"push 115\n"
		::);
	goto d_handler;
handler116:
	asm volatile (
		"push 0\n"
		"push 116\n"
		::);
	goto d_handler;
handler117:
	asm volatile (
		"push 0\n"
		"push 117\n"
		::);
	goto d_handler;
handler118:
	asm volatile (
		"push 0\n"
		"push 118\n"
		::);
	goto d_handler;
handler119:
	asm volatile (
		"push 0\n"
		"push 119\n"
		::);
	goto d_handler;
handler120:
	asm volatile (
		"push 0\n"
		"push 120\n"
		::);
	goto d_handler;
handler121:
	asm volatile (
		"push 0\n"
		"push 121\n"
		::);
	goto d_handler;
handler122:
	asm volatile (
		"push 0\n"
		"push 122\n"
		::);
	goto d_handler;
handler123:
	asm volatile (
		"push 0\n"
		"push 123\n"
		::);
	goto d_handler;
handler124:
	asm volatile (
		"push 0\n"
		"push 124\n"
		::);
	goto d_handler;
handler125:
	asm volatile (
		"push 0\n"
		"push 125\n"
		::);
	goto d_handler;
handler126:
	asm volatile (
		"push 0\n"
		"push 126\n"
		::);
	goto d_handler;
handler127:
	asm volatile (
		"push 0\n"
		"push 127\n"
		::);
	goto d_handler;
handler128:
	asm volatile (
		"push 0\n"
		"push 128\n"
		::);
	goto d_handler;
handler129:
	asm volatile (
		"push 0\n"
		"push 129\n"
		::);
	goto d_handler;
handler130:
	asm volatile (
		"push 0\n"
		"push 130\n"
		::);
	goto d_handler;
handler131:
	asm volatile (
		"push 0\n"
		"push 131\n"
		::);
	goto d_handler;
handler132:
	asm volatile (
		"push 0\n"
		"push 132\n"
		::);
	goto d_handler;
handler133:
	asm volatile (
		"push 0\n"
		"push 133\n"
		::);
	goto d_handler;
handler134:
	asm volatile (
		"push 0\n"
		"push 134\n"
		::);
	goto d_handler;
handler135:
	asm volatile (
		"push 0\n"
		"push 135\n"
		::);
	goto d_handler;
handler136:
	asm volatile (
		"push 0\n"
		"push 136\n"
		::);
	goto d_handler;
handler137:
	asm volatile (
		"push 0\n"
		"push 137\n"
		::);
	goto d_handler;
handler138:
	asm volatile (
		"push 0\n"
		"push 138\n"
		::);
	goto d_handler;
handler139:
	asm volatile (
		"push 0\n"
		"push 139\n"
		::);
	goto d_handler;
handler140:
	asm volatile (
		"push 0\n"
		"push 140\n"
		::);
	goto d_handler;
handler141:
	asm volatile (
		"push 0\n"
		"push 141\n"
		::);
	goto d_handler;
handler142:
	asm volatile (
		"push 0\n"
		"push 142\n"
		::);
	goto d_handler;
handler143:
	asm volatile (
		"push 0\n"
		"push 143\n"
		::);
	goto d_handler;
handler144:
	asm volatile (
		"push 0\n"
		"push 144\n"
		::);
	goto d_handler;
handler145:
	asm volatile (
		"push 0\n"
		"push 145\n"
		::);
	goto d_handler;
handler146:
	asm volatile (
		"push 0\n"
		"push 146\n"
		::);
	goto d_handler;
handler147:
	asm volatile (
		"push 0\n"
		"push 147\n"
		::);
	goto d_handler;
handler148:
	asm volatile (
		"push 0\n"
		"push 148\n"
		::);
	goto d_handler;
handler149:
	asm volatile (
		"push 0\n"
		"push 149\n"
		::);
	goto d_handler;
handler150:
	asm volatile (
		"push 0\n"
		"push 150\n"
		::);
	goto d_handler;
handler151:
	asm volatile (
		"push 0\n"
		"push 151\n"
		::);
	goto d_handler;
handler152:
	asm volatile (
		"push 0\n"
		"push 152\n"
		::);
	goto d_handler;
handler153:
	asm volatile (
		"push 0\n"
		"push 153\n"
		::);
	goto d_handler;
handler154:
	asm volatile (
		"push 0\n"
		"push 154\n"
		::);
	goto d_handler;
handler155:
	asm volatile (
		"push 0\n"
		"push 155\n"
		::);
	goto d_handler;
handler156:
	asm volatile (
		"push 0\n"
		"push 156\n"
		::);
	goto d_handler;
handler157:
	asm volatile (
		"push 0\n"
		"push 157\n"
		::);
	goto d_handler;
handler158:
	asm volatile (
		"push 0\n"
		"push 158\n"
		::);
	goto d_handler;
handler159:
	asm volatile (
		"push 0\n"
		"push 159\n"
		::);
	goto d_handler;
handler160:
	asm volatile (
		"push 0\n"
		"push 160\n"
		::);
	goto d_handler;
handler161:
	asm volatile (
		"push 0\n"
		"push 161\n"
		::);
	goto d_handler;
handler162:
	asm volatile (
		"push 0\n"
		"push 162\n"
		::);
	goto d_handler;
handler163:
	asm volatile (
		"push 0\n"
		"push 163\n"
		::);
	goto d_handler;
handler164:
	asm volatile (
		"push 0\n"
		"push 164\n"
		::);
	goto d_handler;
handler165:
	asm volatile (
		"push 0\n"
		"push 165\n"
		::);
	goto d_handler;
handler166:
	asm volatile (
		"push 0\n"
		"push 166\n"
		::);
	goto d_handler;
handler167:
	asm volatile (
		"push 0\n"
		"push 167\n"
		::);
	goto d_handler;
handler168:
	asm volatile (
		"push 0\n"
		"push 168\n"
		::);
	goto d_handler;
handler169:
	asm volatile (
		"push 0\n"
		"push 169\n"
		::);
	goto d_handler;
handler170:
	asm volatile (
		"push 0\n"
		"push 170\n"
		::);
	goto d_handler;
handler171:
	asm volatile (
		"push 0\n"
		"push 171\n"
		::);
	goto d_handler;
handler172:
	asm volatile (
		"push 0\n"
		"push 172\n"
		::);
	goto d_handler;
handler173:
	asm volatile (
		"push 0\n"
		"push 173\n"
		::);
	goto d_handler;
handler174:
	asm volatile (
		"push 0\n"
		"push 174\n"
		::);
	goto d_handler;
handler175:
	asm volatile (
		"push 0\n"
		"push 175\n"
		::);
	goto d_handler;
handler176:
	asm volatile (
		"push 0\n"
		"push 176\n"
		::);
	goto d_handler;
handler177:
	asm volatile (
		"push 0\n"
		"push 177\n"
		::);
	goto d_handler;
handler178:
	asm volatile (
		"push 0\n"
		"push 178\n"
		::);
	goto d_handler;
handler179:
	asm volatile (
		"push 0\n"
		"push 179\n"
		::);
	goto d_handler;
handler180:
	asm volatile (
		"push 0\n"
		"push 180\n"
		::);
	goto d_handler;
handler181:
	asm volatile (
		"push 0\n"
		"push 181\n"
		::);
	goto d_handler;
handler182:
	asm volatile (
		"push 0\n"
		"push 182\n"
		::);
	goto d_handler;
handler183:
	asm volatile (
		"push 0\n"
		"push 183\n"
		::);
	goto d_handler;
handler184:
	asm volatile (
		"push 0\n"
		"push 184\n"
		::);
	goto d_handler;
handler185:
	asm volatile (
		"push 0\n"
		"push 185\n"
		::);
	goto d_handler;
handler186:
	asm volatile (
		"push 0\n"
		"push 186\n"
		::);
	goto d_handler;
handler187:
	asm volatile (
		"push 0\n"
		"push 187\n"
		::);
	goto d_handler;
handler188:
	asm volatile (
		"push 0\n"
		"push 188\n"
		::);
	goto d_handler;
handler189:
	asm volatile (
		"push 0\n"
		"push 189\n"
		::);
	goto d_handler;
handler190:
	asm volatile (
		"push 0\n"
		"push 190\n"
		::);
	goto d_handler;
handler191:
	asm volatile (
		"push 0\n"
		"push 191\n"
		::);
	goto d_handler;
handler192:
	asm volatile (
		"push 0\n"
		"push 192\n"
		::);
	goto d_handler;
handler193:
	asm volatile (
		"push 0\n"
		"push 193\n"
		::);
	goto d_handler;
handler194:
	asm volatile (
		"push 0\n"
		"push 194\n"
		::);
	goto d_handler;
handler195:
	asm volatile (
		"push 0\n"
		"push 195\n"
		::);
	goto d_handler;
handler196:
	asm volatile (
		"push 0\n"
		"push 196\n"
		::);
	goto d_handler;
handler197:
	asm volatile (
		"push 0\n"
		"push 197\n"
		::);
	goto d_handler;
handler198:
	asm volatile (
		"push 0\n"
		"push 198\n"
		::);
	goto d_handler;
handler199:
	asm volatile (
		"push 0\n"
		"push 199\n"
		::);
	goto d_handler;
handler200:
	asm volatile (
		"push 0\n"
		"push 200\n"
		::);
	goto d_handler;
handler201:
	asm volatile (
		"push 0\n"
		"push 201\n"
		::);
	goto d_handler;
handler202:
	asm volatile (
		"push 0\n"
		"push 202\n"
		::);
	goto d_handler;
handler203:
	asm volatile (
		"push 0\n"
		"push 203\n"
		::);
	goto d_handler;
handler204:
	asm volatile (
		"push 0\n"
		"push 204\n"
		::);
	goto d_handler;
handler205:
	asm volatile (
		"push 0\n"
		"push 205\n"
		::);
	goto d_handler;
handler206:
	asm volatile (
		"push 0\n"
		"push 206\n"
		::);
	goto d_handler;
handler207:
	asm volatile (
		"push 0\n"
		"push 207\n"
		::);
	goto d_handler;
handler208:
	asm volatile (
		"push 0\n"
		"push 208\n"
		::);
	goto d_handler;
handler209:
	asm volatile (
		"push 0\n"
		"push 209\n"
		::);
	goto d_handler;
handler210:
	asm volatile (
		"push 0\n"
		"push 210\n"
		::);
	goto d_handler;
handler211:
	asm volatile (
		"push 0\n"
		"push 211\n"
		::);
	goto d_handler;
handler212:
	asm volatile (
		"push 0\n"
		"push 212\n"
		::);
	goto d_handler;
handler213:
	asm volatile (
		"push 0\n"
		"push 213\n"
		::);
	goto d_handler;
handler214:
	asm volatile (
		"push 0\n"
		"push 214\n"
		::);
	goto d_handler;
handler215:
	asm volatile (
		"push 0\n"
		"push 215\n"
		::);
	goto d_handler;
handler216:
	asm volatile (
		"push 0\n"
		"push 216\n"
		::);
	goto d_handler;
handler217:
	asm volatile (
		"push 0\n"
		"push 217\n"
		::);
	goto d_handler;
handler218:
	asm volatile (
		"push 0\n"
		"push 218\n"
		::);
	goto d_handler;
handler219:
	asm volatile (
		"push 0\n"
		"push 219\n"
		::);
	goto d_handler;
handler220:
	asm volatile (
		"push 0\n"
		"push 220\n"
		::);
	goto d_handler;
handler221:
	asm volatile (
		"push 0\n"
		"push 221\n"
		::);
	goto d_handler;
handler222:
	asm volatile (
		"push 0\n"
		"push 222\n"
		::);
	goto d_handler;
handler223:
	asm volatile (
		"push 0\n"
		"push 223\n"
		::);
	goto d_handler;
handler224:
	asm volatile (
		"push 0\n"
		"push 224\n"
		::);
	goto d_handler;
handler225:
	asm volatile (
		"push 0\n"
		"push 225\n"
		::);
	goto d_handler;
handler226:
	asm volatile (
		"push 0\n"
		"push 226\n"
		::);
	goto d_handler;
handler227:
	asm volatile (
		"push 0\n"
		"push 227\n"
		::);
	goto d_handler;
handler228:
	asm volatile (
		"push 0\n"
		"push 228\n"
		::);
	goto d_handler;
handler229:
	asm volatile (
		"push 0\n"
		"push 229\n"
		::);
	goto d_handler;
handler230:
	asm volatile (
		"push 0\n"
		"push 230\n"
		::);
	goto d_handler;
handler231:
	asm volatile (
		"push 0\n"
		"push 231\n"
		::);
	goto d_handler;
handler232:
	asm volatile (
		"push 0\n"
		"push 232\n"
		::);
	goto d_handler;
handler233:
	asm volatile (
		"push 0\n"
		"push 233\n"
		::);
	goto d_handler;
handler234:
	asm volatile (
		"push 0\n"
		"push 234\n"
		::);
	goto d_handler;
handler235:
	asm volatile (
		"push 0\n"
		"push 235\n"
		::);
	goto d_handler;
handler236:
	asm volatile (
		"push 0\n"
		"push 236\n"
		::);
	goto d_handler;
handler237:
	asm volatile (
		"push 0\n"
		"push 237\n"
		::);
	goto d_handler;
handler238:
	asm volatile (
		"push 0\n"
		"push 238\n"
		::);
	goto d_handler;
handler239:
	asm volatile (
		"push 0\n"
		"push 239\n"
		::);
	goto d_handler;
handler240:
	asm volatile (
		"push 0\n"
		"push 240\n"
		::);
	goto d_handler;
handler241:
	asm volatile (
		"push 0\n"
		"push 241\n"
		::);
	goto d_handler;
handler242:
	asm volatile (
		"push 0\n"
		"push 242\n"
		::);
	goto d_handler;
handler243:
	asm volatile (
		"push 0\n"
		"push 243\n"
		::);
	goto d_handler;
handler244:
	asm volatile (
		"push 0\n"
		"push 244\n"
		::);
	goto d_handler;
handler245:
	asm volatile (
		"push 0\n"
		"push 245\n"
		::);
	goto d_handler;
handler246:
	asm volatile (
		"push 0\n"
		"push 246\n"
		::);
	goto d_handler;
handler247:
	asm volatile (
		"push 0\n"
		"push 247\n"
		::);
	goto d_handler;
handler248:
	asm volatile (
		"push 0\n"
		"push 248\n"
		::);
	goto d_handler;
handler249:
	asm volatile (
		"push 0\n"
		"push 249\n"
		::);
	goto d_handler;
handler250:
	asm volatile (
		"push 0\n"
		"push 250\n"
		::);
	goto d_handler;
handler251:
	asm volatile (
		"push 0\n"
		"push 251\n"
		::);
	goto d_handler;
handler252:
	asm volatile (
		"push 0\n"
		"push 252\n"
		::);
	goto d_handler;
handler253:
	asm volatile (
		"push 0\n"
		"push 253\n"
		::);
	goto d_handler;
handler254:
	asm volatile (
		"push 0\n"
		"push 254\n"
		::);
	goto d_handler;
handler255:
	asm volatile (
		"push 0\n"
		"push 255\n"
		::);
d_handler:
	asm volatile (
		"push ebp\n"
		"push edi\n"
		"push esi\n"
		"push edx\n"
		"push ecx\n"
		"push ebx\n"
		"push eax\n"

		"push esp\n"
		"call default_interrupt_handler\n"
		"add esp, 4\n"

		"pop eax\n"
		"pop ebx\n"
		"pop ecx\n"
		"pop edx\n"
		"pop esi\n"
		"pop edi\n"
		"pop ebp\n"
		"add esp, 8\n"
		"iret" );
beach:
	return 256;
}

