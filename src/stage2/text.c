#include "text.h"
#include "screen.h"
#include "font.h"

void drawChar(char c, uint16_t x, uint16_t y) {
	if(c <= ' ' || c >= 127) return;
	uint16_t pitch = vbeInfo.pitch;
	uint8_t* ptr = (uint8_t*)backBuffer + (y*pitch + x*3);
	uint8_t fontIndex = c - '!';
	for(uint16_t i = fontIndex*16*8; i <(fontIndex+1)*16*8; ++i) {
		if(i != fontIndex*16*8 && i%fontW == 0) {
			ptr += pitch-((fontW-1)*3)-3;
		}
		uint8_t v = font[i];
		*(ptr) = v;
		*(ptr+1) = v;
		*(ptr+2) = v;

		ptr += 3;
	}
}

void drawStr(char* str, uint16_t x, uint16_t y) {
	uint16_t startX = x;
	while(*str != '\0') {
		if(*str == '\n') {
			x = startX;
			y += 16;
		} else {
			drawChar(*str, x, y);
			x += 8;
		}
		++str;
	}
}
