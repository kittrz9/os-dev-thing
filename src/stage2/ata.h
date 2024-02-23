#ifndef ATA_H
#define ATA_H

#include <stdint.h>

uint8_t initATA(void);
uint8_t readATA(uint32_t lba, uint8_t count, uint16_t* buf);

#endif
