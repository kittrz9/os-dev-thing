#include "term.h"
#include <stdint.h>
#include "serial.h"
#include "screen.h"
#include "text.h"

char term[80*30];
uint16_t cursor = 0;

void initTerm(void) {
	for(uint16_t i = 0; i < 80*30; ++i) {
		term[i] = ' ';
	}
}
void drawTerm(void) {
	static uint8_t hue = 0;
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

	for(uint8_t y = 0; y < 30; ++y) {
		for(uint8_t x = 0; x < 80; ++x) {
			drawChar(term[y*80 + x], x*8,y*16);
		}
	}
	uint16_t cursorX = (cursor%80) * 8;
	uint16_t cursorY = (cursor/80) * 16;
	drawFilledRect(cursorX, cursorY, cursorX+8, cursorY+16, 0xffffff);

	refreshScreen();
}

void cursorBoundsCheck(void) {
	if(cursor > 80*30-1) {
		for(uint16_t i = 0; i < 80*29; ++i) {
			term[i] = term[i+80];
		}
		for(uint16_t i = 80*29; i < 80*30; ++i) {
			term[i] = ' ';
		}

		cursor = 29*80;
	}
}

// maybe should change these names later
void putc(char c) {
	if(c == '\n') {
		cursor += 80;
		cursor -= cursor%80;
	}
	if(c == '\b' && cursor != 0) {
		--cursor;
		if(cursor%80 == 79) {
			while(term[cursor] == ' ' && cursor%80 != 0){
				--cursor;
			};
		}
		term[cursor] = ' ';
		return;
	}
	if(c == '\t') {
		cursor += 4;
	}

	if(c >= ' ' && c <= '~') {
		term[cursor] = c;
		++cursor;
	}
	cursorBoundsCheck();
}

void puts(char* str) {
	while(*str != '\0') {
		putc(*str);
		++str;
	}
}
