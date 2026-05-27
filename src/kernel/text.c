#include "text.h"
#include "screen.h"
#include "font.h"

void drawChar(char c, uint16_t x, uint16_t y) {
	if(c <= ' ' || c >= 127) return;
	uint16_t pitch = vbeInfo.pitch;
	uint8_t* ptr = (uint8_t*)backBuffer + (y*pitch + x*3);
	uint8_t fontIndex = c - '!';
	for(uint16_t i = fontIndex*16; i <(fontIndex+1)*16; ++i) {
		// honestly would probably be a good idea to move font data to its own file away from the kernel
		// could probably even have everything regarding the terminal and shell be its own thing once I make syscalls for dealing with the framebuffer and tasks
		uint8_t v = font[i];
		for(uint8_t i = 0; i < 8; ++i) {
			*(ptr) = (v & 0x80 ? 255 : 0);
			*(ptr+1) = (v & 0x80 ? 255 : 0);
			*(ptr+2) = (v & 0x80 ? 255 : 0);
			v <<= 1;

			ptr += 3;
		}
		ptr += pitch-((fontW-1)*3)-3;
	}
}

void drawStr(char* str, uint16_t x, uint16_t y) {
	uint16_t startX = x;
	while(*str != '\0') {
		if(*str == '\n') {
			x = startX;
			y += 16;
		} else {
			if(x >= 640) {
				x = startX;
				y += 16;
			}
			drawChar(*str, x, y);
			x += 8;
		}
		++str;
	}
}
