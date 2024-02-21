#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

void handleScancode(uint8_t scanecode);

extern char keyboardStr[32];

#endif
