#include "timer.h"

#include "io.h"
#include "serial.h"

volatile uint32_t countDown = 0;

void timerSetFreqDiv(uint8_t channel, enum TIMER_MODE mode, uint16_t freqDiv) {
	uint8_t flags = channel<<6 | mode | 0x30;
	outb(PITMODE, flags);
	outb(PITDATA0+channel, (freqDiv&0xFF));
	outb(PITDATA0+channel, (freqDiv&0xFF00)>>8);
}
void timerSetFreq(uint8_t channel, enum TIMER_MODE mode, uint32_t freq) {
	uint32_t freqDiv = 1193180/freq;
	timerSetFreqDiv(channel, mode, freqDiv);
}

void sleep(uint32_t ms) {
	countDown = ms;
	while(countDown != 0) {
	}
}

