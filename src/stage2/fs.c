#include "fs.h"
#include <stddef.h>
#include "string.h"
#include "ata.h"
#include "term.h"
#include "mbr.h"
#include "serial.h"

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

// having these get put into bss made them unitialized, I should probably init bss to 0 myself but whatever this works for now
__attribute__((section("data"))) uint32_t fsSize = 0;
__attribute__((section("data"))) uint32_t fsLBA = 0;

void initFS(void) {
	uint8_t buffer[512];
	readATA(0, 1, (uint16_t*)buffer);
	mbrPartition* fsPart = (mbrPartition*)(buffer+PARTITION2_OFFSET);

	fsSize = fsPart->size;
	fsLBA = fsPart->lba;
	readATA(fsLBA, 1, (uint16_t*)buffer);
	ustarHeader* header = (ustarHeader*)buffer;
	if(memcmp(header->ustarStr, "ustar", 5) != 0) {
		fsSize = 0;
		fsLBA = 0;
		puts("invalid filesystem\n");
	}
}

void listFiles(void) {
	uint8_t buffer[512];

	if(fsSize == 0 || fsLBA == 0) {
		puts("file system not initialized or invalid\n");
		return;
	}

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

// just dumping everything at the end of stage2 in ram
// really need to make some allocator eventually
extern uint32_t stage2End;

void printFile(char* name) {
	uint8_t buffer[512];

	if(fsSize == 0) {
		puts("file system not initialized or invalid\n");
		return;
	}

	for(uint32_t i = fsLBA; i < fsLBA+fsSize; ++i) {
		readATA(i, 1, (uint16_t*)buffer);
		ustarHeader* header = (ustarHeader*)buffer;
		if(memcmp(header->ustarStr, "ustar", 5) == 0) {
			if(strcmp(header->name, name) == 0) {
				uint32_t fileSize = parseOctStr(header->size);
				readATA(i+1, fileSize/512 + (fileSize%512!=0), (uint16_t*)&stage2End);
				puts((char*)&stage2End);
				return;
			}
		}
	}

	puts("file not found\n");
	return;
}

