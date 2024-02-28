#include "files.h"
#include "fs.h"
#include "term.h"
#include "ata.h"
#include "string.h"
#include "serial.h"
#include "pageAlloc.h"

void printFile(char* name) {
	uint8_t* buffer = pageAlloc(getFileSize(name)); // should probably not be traversing the file system twice here but whatever
	if(readFile(name, buffer)) {
		puts((char*)buffer);
	} else {
		puts("file not found\n");
	}
	// memory leak because I can't free pages yet lmao
	return;
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

