#include "serial.h"
#include "io.h"

void stage2(void) {
	initSerial();

	serialWriteStr("waga baba bobo\n");

	__asm__ volatile ("cli; hlt");
}

