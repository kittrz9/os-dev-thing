#include "serial.h"
#include "io.h"

void stage2(void) {
	initSerial();

	serialWriteStr("waga baba bobo\n");
	serialWriteHex32(0xbee5bee5);

	__asm__ volatile ("cli; hlt");
}

