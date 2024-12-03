#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

void handleScancode(uint8_t scanecode);

char readKey(void);

#endif
