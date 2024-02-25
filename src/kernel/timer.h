#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

// https://wiki.osdev.org/Programmable_Interval_Timer#I.2FO_Ports
#define PITDATA0 0x40
#define PITDATA1 0x41
#define PITDATA2 0x42
#define PITMODE 0x43

enum TIMER_MODE {
	TIMER_IRQ,
	TIMER_HW_ONE,
	TIMER_RATE,
	TIMER_SQUARE,
	TIMER_SW_STROBE,
	TIMER_HW_STROBE,
	TIMER_RATE2,
	TIMER_SQUARE2,
};

void timerSetFreqDiv(uint8_t channel, enum TIMER_MODE mode, uint16_t freqDiv);
void timerSetFreq(uint8_t channel, enum TIMER_MODE mode, uint32_t freq);
void sleep(uint32_t ms);

#endif
