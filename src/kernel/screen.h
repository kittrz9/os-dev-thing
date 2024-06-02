#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include "vbe.h"

extern uint8_t* backBuffer;
void initScreen(void);

void drawFilledRect(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint32_t color);
void refreshScreen(void);

uint32_t hueToRgb(uint8_t hue);


#endif 
