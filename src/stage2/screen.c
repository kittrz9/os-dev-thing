#include "screen.h"
#include "serial.h"

struct vbe_mode_info_structure vbeInfo;

/*
really stupid workaround to make the back buffer not collide with 0xA0000,
which for some reason still reads from the framebuffer even though I'm not
using any VGA or VESA mode that would actually make sense with that strange
memory layout

this will need to be changed as soon as I actually start to figure out actual
memory management
*/
uint8_t* backBuffer = (uint8_t*)0x100000;

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

void refreshScreen() {
	uint8_t* ptr = (uint8_t*)vbeInfo.framebuffer;
	for(uint32_t i = 0; i < 640*480*3; ++i) {
		ptr[i] = backBuffer[i];
	}
}

