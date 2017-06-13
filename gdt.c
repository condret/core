#include <init.h>
#include <ktypes.h>

ut8 generate_access_byte (bool rw, bool dc, bool exec, bool seg, ut8 priv, bool p)
{
	ut8 ab = 0;
	ab |= ((rw & true)<<1);
	ab |= ((dc & true)<<2);
	ab |= ((exec & true)<<3);
	ab |= ((seg & true)<<4);
	ab |= ((priv & 0x3)<<5);
	return (ab | ((p & true)<<7));
}

void set_gdt_entry (ut64 *gdt, ut16 i, ut32 base, ut32 limit, ut8 abyte, gdt_flags_t flags)
{
	gdt[i] = (limit & 0xffff);
	gdt[i] |= ((ut64)(base & 0xffffff)) << 16;
	gdt[i] |= ((ut64) abyte) << 40;
	gdt[i] |= ((ut64)(limit & 0xf0000)) << 32;
	gdt[i] |= ((ut64) flags) << 52;
	gdt[i] |= ((ut64)(base & 0xff000000)) << 32;
}

void load_gdt (ut64 *gdt, ut16 gdt_sz)
{
	GdtPointer gdtp = {
		.limit = (gdt_sz * 8) - 1,
		.pointer = gdt,
	};
	asm volatile (
		"lgdt %0\n"
		"mov ax, 0x10\n"
		"mov ds, ax\n"
		"mov es, ax\n"
		"mov ss, ax\n"
		"mov gs, ax\n"
		"mov fs, ax\n"
		"ljmp 0x8:end_of_load_gdt\n"
		"end_of_load_gdt:\n"
		:: "m" (gdtp)
	);
}
