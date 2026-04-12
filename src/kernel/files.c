#include "files.h"
#include "fs.h"
#include "term.h"
#include "ata.h"
#include "string.h"
#include "serial.h"
#include "pageAlloc.h"

void printFile(char* name) {
	uint32_t fileSize = getFileSize(name); // should probably not be traversing the file system twice here but whatever
	uint8_t* buffer = pageAlloc(fileSize); 
	if(readFile(name, buffer)) {
		puts((char*)buffer);
	} else {
		puts("file not found\n");
	}
	pageFree(buffer, fileSize);
	return;
}

void listFiles(void) {
	uint8_t buffer[512];

	if(fsSize == 0 || fsLBA == 0) {
		puts("file system not initialized or invalid\n");
		return;
	}

	puts("files: \n");

	uint32_t currentLBA = indicesLBA;

	readATA(currentLBA, 1, (uint16_t*)buffer);

	uint8_t* entry = &buffer[512 - 64];

	while(*entry != 0) {
		//serialWriteHex32(*entry);
		if(*entry == 0x12) {
			puts(entry+0x22);
			puts(", size: ");
			puts(hex32Str(*(uint32_t*)(entry+0x1a)));
			putc('\n');
		}
		entry -= 64;
		if(entry < buffer) {
			--currentLBA;
			readATA(currentLBA, 1, (uint16_t*)buffer);
			entry = &buffer[512 - 64];
		}
	}

	/*for(uint32_t i = fsLBA; i < fsLBA+fsSize; ++i) {
		readATA(i, 1, (uint16_t*)buffer);
		ustarHeader* header = (ustarHeader*)buffer;
		if(memcmp(header->ustarStr, "ustar", 5) == 0) {
			puts(header->name);
			puts(", size: ");
			puts(hex32Str(parseOctStr(header->size)));
			putc('\n');
		}
	}*/

	return;
}

