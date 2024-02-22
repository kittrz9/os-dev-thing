#include "serial.h"
#include "io.h"
#include "screen.h"
#include "pic.h"
#include "timer.h"
#include "text.h"
#include "keyboard.h"
#include "term.h"

void loadIDT(void);

void stage2(void) {
	initSerial();

	vbeInfo = *(struct vbe_mode_info_structure*)0x1000;

	serialWriteStr("waga baba bobo\n");
	serialWriteHex32(0xbee5bee5);

	loadIDT();

	PICInit();

	uint8_t id = 0;
	do {
		PICSetMask(id);
		++id;
	} while(id != 0); // funny overflow moment
	PICClearMask(1); // keyboard

	//timerSetFreq(2, TIMER_SQUARE2, 440);
	timerSetFreqDiv(0, TIMER_SQUARE2, 1194); // ~1ms
	PICClearMask(0); // timer
	/*uint8_t tmp = inb(0x61);
	if(tmp != (tmp|3)){
		outb(0x61, tmp | 3);
	}*/

	initTerm();

	puts("https://kittrz.gay/\n");

	uint8_t hue = 0;
	while(1) {
		uint32_t color = hueToRgb(hue);
		// assuming color format, cringe but works in qemu for now lmao
		uint8_t b = (color&0xff);
		uint8_t g = (color&0xff00)>>8;
		uint8_t r = (color&0xff0000)>>16;
		uint8_t* ptr = backBuffer;
		uint16_t pitch = vbeInfo.pitch;
		for(uint16_t line = 0; line < 480; ++line) {
			for(uint16_t i = 0; i < 640*3; i+=3) {
				*(ptr+i) = b;
				*(ptr+i+1) = g;
				*(ptr+i+2) = r;
			}
			ptr += pitch;
		}
		++hue;

		drawTerm();

		refreshScreen();

		sleep(20);

	}

	serialWriteStr("done\n");

	__asm__ volatile ("cli; hlt");
}

