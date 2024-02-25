#include "serial.h"
#include "io.h"
#include "vbe.h"
#include "ata.h"
#include "fs.h"

void stage2(struct vbe_mode_info_structure* vbePtr) {
	initSerial();

	serialWriteStr("stage2 loaded at: ");
	serialWriteHex32(stage2);
	serialWriteStr("\n");

	vbeInfo = *vbePtr;

	if(!initATA()) {
		initFS();
		void (*kernelAddr)(struct vbe_mode_info_structure* vbeAddr) = 0x100000;
		readFile("kernel.bin", (uint8_t*)0x100000);
		(*kernelAddr)(vbePtr);
		while(1);
	}

	serialWriteStr("done\n");

	__asm__ volatile ("cli; hlt");
}

