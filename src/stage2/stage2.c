#include "serial.h"
#include "io.h"
#include "vbe.h"
#include "ata.h"
#include "fs.h"

void stage2(struct vbe_mode_info_structure* vbePtr) {
	initSerial();

	serialWriteStr("stage2 loaded at: ");
	serialWriteHex32((uint32_t)stage2);
	serialWriteStr("\n");

	if(!initATA()) {
		initFS();

		// fixes warning about casting to a function pointer
		typedef void kernelAddr_t(struct vbe_mode_info_structure*);
		kernelAddr_t* kernelAddr = (kernelAddr_t*)0x100000;
		readFile("kernel.bin", (uint8_t*)0x100000);
		(*kernelAddr)(vbePtr);
	}

	serialWriteStr("done\n");

	__asm__ volatile ("cli; hlt");
}

