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
uint8_t backBuffer[640*480*3];

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

void drawFilledRect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint32_t color) {
	uint16_t pitch = vbeInfo.pitch;
	uint8_t* ptr = (uint8_t*)backBuffer + (y*pitch + x*3);
	uint16_t startX = x;
	uint8_t b = (color&0xff);
	uint8_t g = (color&0xff00)>>8;
	uint8_t r = (color&0xff0000)>>16;

	while(y < y2) {
		while(x < x2) {
			if(ptr+2 > backBuffer + 640*480*3) {
				serialWriteStr("backbuffer overflow\n");
				serialWriteStr("x: ");
				serialWriteHex32(x);
				serialWriteStr("y: ");
				serialWriteHex32(y);
				asm volatile("cli;hlt;");
			}
			*(ptr) = b;
			*(ptr+1) = g;
			*(ptr+2) = r;

			ptr += 3;
			++x;
		}
		++y;
		x = startX;
		ptr += pitch-((x2-x)*3);
	}
}
