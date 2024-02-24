#include "fs.h"
#include <stddef.h>
#include "string.h"
#include "ata.h"
#include "term.h"
#include "mbr.h"

// https://wiki.osdev.org/USTAR

typedef struct {
	char name[100];
	char mode[8];
	char ownerId[8];
	char groupId[8];
	char size[12];
	char modifyTime[12];
	char checksum[8];
	char typeFlag;
	char linkedFile[100];
	char ustarStr[5];
	char ustarVersion[2];
	char ownerName[32];
	char groupName[32];
	char devMajorNumber[8];
	char devMinorNumber[8];
	char prefix[155];
} ustarHeader;


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

// probably could be moved and used elsewhere
char* hex32Str(uint32_t n) {
	char hexLUT[] = "0123456789ABCDEF";
	static char str[11];
	strcpy(str, "0x00000000");

	char* ptr = str + 8;
	while(n != 0) {
		*(ptr+1) = hexLUT[n & 0x0F];
		*(ptr+0) = hexLUT[(n & 0xF0)>>4];
		n = n >> 8;
		ptr -= 2;
	}

	return str;
}
void listFiles(void) {
	uint8_t buffer[512];
	readATA(0, 1, (uint16_t*)buffer);
	mbrPartition* fsPart = (mbrPartition*)(buffer+PARTITION2_OFFSET);

	uint32_t fsSize = fsPart->size;
	uint32_t fsLBA = fsPart->lba;
	puts("files: \n");

	for(uint32_t i = fsLBA; i < fsLBA+fsSize; ++i) {
		readATA(i, 1, (uint16_t*)buffer);
		ustarHeader* header = (ustarHeader*)buffer;
		if(memcmp(header->ustarStr, "ustar", 5) == 0) {
			puts(header->name);
			puts(", size: ");
			puts(hex32Str(parseOctStr(header->size)));
			putc('\n');
		}
	}

	return;
}
