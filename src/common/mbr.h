#ifndef MBR_H
#define MBR_H

#include <stdint.h>

typedef struct {
	uint8_t bootable;
	uint8_t startingHead;
	uint8_t startingSect;
	uint8_t startingCyl;
	uint8_t systemId;
	uint8_t endingHead;
	uint8_t endingSect;
	uint8_t endingCyl;
	uint32_t lba;
	uint32_t size;
} mbrPartition;

#define PARTITION1_OFFSET 0x1be
#define PARTITION2_OFFSET 0x1ce
#define PARTITION3_OFFSET 0x1de
#define PARTITION4_OFFSET 0x1ee

#endif
