#ifndef	INIT_H
#define	INIT_H

#include <ktypes.h>

typedef enum {
	GDT_FLG_16BIT = 0x0,
	GDT_FLG_LONGMODE = 0x2,
	GDT_FLG_32BIT = 0x4,
	GDT_FLG_16BIT_4K = 0x8,
	GDT_FLG_LONGMODE_4K = 0xa,
	GDT_FLG_32BIT_4K = 0xc
} gdt_flags_t;

typedef struct __attribute__((packed)) gdt_pointer_t {
	ut16 limit;
	ut64 *pointer;
} GdtPointer;

ut8 generate_access_byte (bool rw, bool dc, bool exec, bool seg, ut8 priv, bool p);
void set_gdt_entry (ut64 *gdt, ut16 i, ut32 base, ut32 limit, ut8 abyte, gdt_flags_t flags);
void load_gdt (ut64 *gdt, ut16 gdt_sz);

typedef enum {
	INTERRUPT_TYPE_TASK_GATE = 5,
	INTERRUPT_TYPE_INTERRUPT_GATE,
	INTERRUPT_TYPE_TRAP_GATE
} interrupt_type_t;

typedef struct __attribute__((packed)) idt_pointer_t {
	ut16 limit;
	ut64 *pointer;
} IdtPointer;

typedef struct cpu_state_t {
	ut32 eax;
	ut32 ebx;
	ut32 ecx;
	ut32 edx;
	ut32 esi;
	ut32 edi;
	ut32 ebp;

	ut32 intr;
	ut32 error;

	ut32 eip;
	ut32 cs;
	ut32 eflags;
	ut32 esp;
	ut32 ss;
} CpuState;

void set_idt_entry (ut64 *idt, ut16 i, ut32 offset, ut16 cs, interrupt_type_t it, ut8 priv, bool p);
void load_idt (ut64 *idt, ut16 idt_sz);
void outb (ut16 port, ut8 data);
ut8 inb (ut16 port);
void default_interrupt_handler (CpuState *cpu);
ut16 register_interrupt_handlers (ut64 *idt);
void init_keyboard ();
void keyboard_handler (CpuState *cpu);
#endif
