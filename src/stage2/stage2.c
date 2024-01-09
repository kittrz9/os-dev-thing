#include "serial.h"
#include "io.h"

// maximum saturation and value
uint32_t hueToRgb(uint8_t hue) {
	// https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
	uint8_t x = 256-(hue*6 % 255);
	if(hue < 43) {
		return 0xff0000 | (256-x)<<8;
	} else if(hue < 85) {
		return 0x00ff00 | x<<16;
	} else if(hue < 128) {
		return 0x00ff00 | (256-x);
	} else if(hue < 170) {
		return 0x0000ff | x<<8;
	} else if(hue < 213) {
		return 0x0000ff | (uint8_t)(256-x)<<16; // to avoid overflow shenanigans
	} else {
		return 0xff0000 | x;
	}
}

void stage2(void) {
	initSerial();

	uint8_t* fbPtr = *(uint32_t*)0x1000;

	serialWriteHex32(fbPtr);

	serialWriteStr("waga baba bobo\n");
	serialWriteHex32(0xbee5bee5);

	uint8_t hue = 0;
	uint8_t j = 0;
	uint8_t k = 0;
	for(uint32_t i = 0; i < 640*480*3; i+=3) {
		//serialWriteHex32(fbPtr+i);
		uint32_t color = hueToRgb(hue);
		//serialWriteHex32(color);
		*(fbPtr+i) = (color & 0xff);
		*(fbPtr+i+1) = (color & 0xff00)>>8;
		*(fbPtr+i+2) = (color & 0xff0000)>>16;
		if(j++%640==0) {
			j=0;
			if(k++ == 100) {
				k = 0;
				++hue;
			}
		}
	}

	serialWriteStr("done\n");

	__asm__ volatile ("cli; hlt");
}

