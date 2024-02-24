#include "ata.h"
#include "io.h"
#include "serial.h"
#include "term.h"

// https://wiki.osdev.org/ATA_PIO_Mode

#define ATA_DATA 0x1f0
#define ATA_ERR  0x1f1
#define ATA_FEATURES 0x1f1
#define ATA_SECTOR_COUNT 0x1f2
#define ATA_LBA_LOW 0x1f3
#define ATA_LBA_MID 0x1f4
#define ATA_LBA_HI 0x1f5
#define ATA_DRIVE 0x1f6
#define ATA_STATUS 0x1f7
#define ATA_COMMAND 0x1f7

#define ATA_STAT_ERR (1 << 0)
#define ATA_STAT_IDX (1 << 1)
#define ATA_STAT_CORR (1 << 2)
#define ATA_STAT_DRQ (1 << 3)
#define ATA_STAT_SRV (1 << 4)
#define ATA_STAT_DF  (1 << 5)
#define ATA_STAT_RDY (1 << 6)
#define ATA_STAT_BSY (1 << 7)

uint8_t pollATA(void) {
	uint8_t status = inb(ATA_STATUS);
	while((status & ATA_STAT_BSY) != 0 && (status & ATA_STAT_DRQ) == 0) {
		status = inb(ATA_STATUS);
		if(status & ATA_STAT_ERR) {
			serialWriteStr("main drive error\n");
			return 1;
		}
	}
	return 0;
}

uint8_t ataInitialized = 1;

uint8_t initATA(void) {
	outb(ATA_DRIVE, 0xe0);
	outb(ATA_SECTOR_COUNT, 0x00);
	outb(ATA_LBA_LOW, 0x00);
	outb(ATA_LBA_MID, 0x00);
	outb(ATA_LBA_HI, 0x00);

	outb(ATA_COMMAND, 0xec); // IDENTIFY command
	uint8_t status = inb(ATA_STATUS);
	if(status == 0) {
		serialWriteStr("main drive not found\n");
		ataInitialized = 0;
		return 1;
	}
	pollATA();

	for(uint16_t i = 0; i < 256; ++i) {
		inb(ATA_DATA); // discarding the info for now
	}

	return 0;
}

uint8_t readATA(uint32_t lba, uint8_t count, uint16_t* buf) {
	if(!ataInitialized) {
		puts("ata not initialized\n");
		return 1;
	}
	
	if(lba > 0x0fffffff) { 
		serialWriteStr("lba too big: ");
		serialWriteHex32(lba);
		return 1;
	};

	outb(ATA_DRIVE, 0xe0 | ((lba>>24)&0xf));

	// stall
	outb(ATA_ERR, 0x00);

	outb(ATA_SECTOR_COUNT, count);
	outb(ATA_LBA_LOW, lba);
	outb(ATA_LBA_MID, lba>>8);
	outb(ATA_LBA_HI, lba>>16);

	outb(ATA_COMMAND, 0x20);
	pollATA();
	for(uint16_t block = 0; block < (count==0?256:count); ++block) {
		for(uint16_t i = 0; i < 256; ++i) {
			buf[i + block*256] = inw(ATA_DATA);
		}
		pollATA();
	}
	return 0;
}
