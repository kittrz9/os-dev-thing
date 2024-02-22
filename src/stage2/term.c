#include "term.h"
#include <stdint.h>
#include "serial.h"

char term[80*30];
uint16_t cursor = 0;

void initTerm(void) {
	for(uint16_t i = 0; i < 80*30; ++i) {
		term[i] = ' ';
	}
}
void drawTerm(void) {
	for(uint8_t y = 0; y < 30; ++y) {
		for(uint8_t x = 0; x < 80; ++x) {
			drawChar(term[y*80 + x], x*8,y*16);
		}
	}
}

// maybe should change these names later
void putc(char c) {
	if(c == '\n') {
		cursor += 80;
		cursor -= cursor%80;
	}
	if(c == '\b' && cursor != 0) {
		do {
			--cursor;
		}while(term[cursor] == ' ');
		term[cursor] = ' ';
		return;
	}
	if(c == '\t') {
		cursor += 4;
	}

	if(cursor > 80*30-1) {
		for(uint16_t i = 0; i < 80*29; ++i) {
			term[i] = term[i+80];
		}
		for(uint16_t i = 80*29; i < 80*30; ++i) {
			term[i] = ' ';
		}

		cursor = 29*80;
	}

	if(c >= ' ' && c <= '~') {
		term[cursor] = c;
		++cursor;
	}
}

void puts(char* str) {
	while(*str != '\0') {
		putc(*str);
		++str;
	}
}
