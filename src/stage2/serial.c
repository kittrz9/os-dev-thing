#include "serial.h"

#include "io.h"

// https://wiki.osdev.org/Serial_Ports#Example_Code

void initSerial(void) {
	outb(COM1INT, 0x00);
	outb(COM1LINECONTROL, 0x80); // set dlab
	outb(COM1BAUDLSB, 0x03); // 38400 baud
	outb(COM1BAUDMSB, 0x00);
	outb(COM1LINECONTROL, 0x03);
	outb(COM1FIFO, 0xC7);
	outb(COM1MODEM, 0x0B);
	outb(COM1MODEM, 0x1E);
	outb(COM1DATA, 0xAE);

	if(inb(COM1DATA) != 0xAE) {
		__asm__ volatile ("cli; hlt");
	}

	outb(COM1MODEM, 0x0F);
	return;
}

enum SERIAL_STATUS {
	SERIAL_DR   = (1<<0),
	SERIAL_OE   = (1<<1),
	SERIAL_PE   = (1<<2),
	SERIAL_FE   = (1<<3),
	SERIAL_BI   = (1<<4),
	SERIAL_THRE = (1<<5),
	SERIAL_TEMT = (1<<6),
	SERIAL_IE   = (1<<7),
};

uint8_t transmitEmpty(void) {
	return inb(COM1 + 5) & 0x20;
}

void serialWriteChar(char c) {
	while(!transmitEmpty());

	outb(COM1DATA, c);
	return;
}

void serialWriteStr(char* str) {
	while(*str != '\0') {
		serialWriteChar(*str++);
	}

	return;
}

