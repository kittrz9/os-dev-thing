#include "serial.h"

#include "io.h"
#include "string.h"

// https://wiki.osdev.org/Serial_Ports#Example_Code

uint8_t serialEnable = 1;

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
		// serial just stopped working on bochs after I started using vesa stuff so this prevents it from just dying due to that
		serialEnable = 0;
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
	return inb(COM1LINESTATUS) & SERIAL_THRE;
}

void serialWriteChar(char c) {
	if(!serialEnable) { return; }
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

char* hex32Str(uint32_t n) {
	char hexLUT[] = "0123456789ABCDEF";
	static char str[11];
	strcpy(str, "0x00000000");

	char* ptr = str + 8;
	while(n != 0) {
		*(ptr+1) = hexLUT[n & 0x0F];
		*(ptr+0) = hexLUT[(n & 0xF0)>>4];
		n = n >> 8;
		ptr -= 2;
	}

	return str;
}


void serialWriteHex32(uint32_t n) {
	serialWriteStr(hex32Str(n));
	
	return;
}

