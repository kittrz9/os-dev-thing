#include "fs.h"
#include <stddef.h>
#include "string.h"
#include "ata.h"
#include "mbr.h"
#include "serial.h"

// https://wiki.osdev.org/USTAR


uint32_t parseOctStr(char* str) {
	uint32_t value = 0;
	size_t len = strlen(str);
	char* c = str;
	while(len-- > 0) {
		value *= 8;
		value += *c - '0';
		++c;
	}
	return value;
}

// having these get put into bss made them unitialized, I should probably init bss to 0 myself but whatever this works for now
uint32_t fsSize = 0;
uint32_t fsLBA = 0;

void initFS(void) {
	uint8_t buffer[512];
	readATA(0, 1, (uint16_t*)buffer);
	mbrPartition* fsPart = (mbrPartition*)(buffer+PARTITION2_OFFSET);

	fsSize = fsPart->size;
	fsLBA = fsPart->lba-1;
	readATA(fsLBA, 1, (uint16_t*)buffer);
	ustarHeader* header = (ustarHeader*)buffer;
	if(memcmp(header->ustarStr, "ustar", 5) != 0) {
		fsSize = 0;
		fsLBA = 0;
		serialWriteStr("invalid filesystem\n");
	}
}

uint32_t getFileSize(char* name) {
	uint8_t buffer[512];

	if(fsSize == 0) {
		serialWriteStr("file system not initialized or invalid\n");
		return 0;
	}

	for(uint32_t i = fsLBA; i < fsLBA+fsSize; ++i) {
		readATA(i, 1, (uint16_t*)buffer);
		ustarHeader* header = (ustarHeader*)buffer;
		if(memcmp(header->ustarStr, "ustar", 5) == 0) {
			uint32_t fileSize = parseOctStr(header->size);
			if(strcmp(header->name, name) == 0) {
				return fileSize;
			} else {
				i += fileSize/512 + (fileSize%512!=0);
			}
		}
	}
	return 0;
}

uint8_t readFile(char* name, uint8_t* dest) {
	uint8_t buffer[512];
	if(fsSize == 0) {
		serialWriteStr("file system not initialized or invalid\n");
		return 1;
	}

	for(uint32_t i = fsLBA; i < fsLBA+fsSize; ++i) {
		readATA(i, 1, (uint16_t*)buffer);
		ustarHeader* header = (ustarHeader*)buffer;
		if(memcmp(header->ustarStr, "ustar", 5) == 0) {
			uint32_t fileSize = parseOctStr(header->size);
			if(strcmp(header->name, name) == 0) {
				readATA(i+1, fileSize/512 + (fileSize%512!=0), (uint16_t*)dest);
				return 1;
			} else {
				i += fileSize/512 + (fileSize%512!=0);
			}
		}
	}
	return 0;
}

