#include "files.h"
#include "fs.h"
#include "term.h"
#include "ata.h"
#include "string.h"
#include "serial.h"

// just dumping everything at the end of stage2 in ram
// really need to make some allocator eventually
extern uint32_t endPage;

void printFile(char* name) {
	if(readFile(name, (uint8_t*)&endPage)) {
		puts((char*)&endPage);
	} else {
		puts("file not found\n");
	}
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

