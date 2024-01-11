#ifndef PIC_H
#define PIC_H

#include <stdint.h>

// https://wiki.osdev.org/PIC
#define PIC1COMMAND 0x20
#define PIC1DATA 0x21
#define PIC2COMMAND 0xA0
#define PIC2DATA 0xA1

void PICSetMask(uint8_t id);
void PICClearMask(uint8_t id);

void PICInit(void);

#endif
