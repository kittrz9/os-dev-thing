#include "serial.h"
#include "io.h"
#include "screen.h"

void loadIDT(void);

void stage2(void) {
	initSerial();

	struct vbe_mode_info_structure* vbeInfo = (struct vbe_mode_info_structure*)0x1000;

	uint8_t* fbPtr = vbeInfo->framebuffer;

	serialWriteStr("waga baba bobo\n");
	serialWriteHex32(0xbee5bee5);

	loadIDT();

	uint8_t hue = 0;
	while(1) {
		uint32_t color = hueToRgb(hue);
		// assuming color format, cringe but works in qemu for now lmao
		uint8_t b = (color&0xff);
		uint8_t g = (color&0xff00)>>8;
		uint8_t r = (color&0xff0000)>>16;
		uint8_t* ptr = fbPtr;
		uint16_t pitch = vbeInfo->pitch;
		for(uint16_t line = 0; line < 480; ++line) {
			ptr += pitch;
			for(uint16_t i = 0; i < 640*3; i+=3) {
				*(ptr+i) = b;
				*(ptr+i+1) = g;
				*(ptr+i+2) = r;
			}
		}
		++hue;

		// stall
		for(volatile uint16_t i = 0; i < UINT16_MAX/4; ++i) {
		}

	}

	serialWriteStr("done\n");

	__asm__ volatile ("cli; hlt");
}

