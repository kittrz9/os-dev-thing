#include "pic.h"

#include "io.h"

// https://wiki.osdev.org/PIC#Masking
void PICSetMask(uint8_t id) {
	uint16_t port = PIC1DATA;
	uint8_t value;

	if(id > 8) {
		port = PIC2DATA;
		id -= 8;
	}
	value = inb(port) | (1 << id);
	outb(port, value);
}

void PICClearMask(uint8_t id) {
	uint16_t port = PIC1DATA;
	uint8_t value;

	if(id > 8) {
		port = PIC2DATA;
		id -= 8;
	}
	value = inb(port) & ~(1 << id);
	outb(port, value);
}

// https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interrupt_Controller

void PICInit(void) {
	// restart PICs
	outb(PIC1COMMAND, 0x11);
	outb(PIC2COMMAND, 0x11);

	// make PIC1 start at 32
	outb(PIC1DATA, 0x20);
	// and PIC2 start at 40
	outb(PIC2DATA, 0x28);

	// cascading
	outb(PIC1DATA, 0x04);
	outb(PIC2DATA, 0x02);



	outb(PIC1DATA, 0x01);
	outb(PIC2DATA, 0x01);
}
