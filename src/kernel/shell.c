#include "shell.h"

#include "keyboard.h"
#include "term.h"
#include "string.h"
#include "elf.h"
#include "pageAlloc.h"
#include "paging.h"
#include "fs.h"

void runShell(void) {
	char cmdBuffer[64];
	memset(cmdBuffer, 0, 64);
	uint8_t cmdBufferPointer = 0;
	char input = readKey();

	putc('>');
	while(input != '\n') {
		if(input != '\0') {
			if(input == '\b' && cmdBufferPointer != 0) {
				cmdBuffer[cmdBufferPointer] = 0;
				--cmdBufferPointer;
				putc(input);
			} else if (input != '\b' && cmdBufferPointer < 64) {
				cmdBuffer[cmdBufferPointer] = input;
				++cmdBufferPointer;
				putc(input);
			}
		}
		input = readKey();
	}

	putc('\n');
	puts(cmdBuffer);
	putc('\n');
	uint32_t fileSize = getFileSize(cmdBuffer);
	if(fileSize == 0) {
		puts("could not find program \"");
		puts(cmdBuffer);
		puts("\"\n");
	} else {
		// need to move this to a separate file
		uint8_t* buffer = pageAlloc(fileSize); 
		readFile(cmdBuffer, buffer);
		elfFileHeader* elfHeader = (elfFileHeader*)buffer;
		elfProgramHeader* pHeaders = (elfProgramHeader*)(buffer + elfHeader->programHeadersOffset);
		elfSectionHeader* sHeaders = (elfSectionHeader*)(buffer + elfHeader->sectionHeadersOffset);
		mapPages(VIRT_TO_PHYS(buffer), (void*)pHeaders[1].virtAddr, BYTES_TO_PAGES(pHeaders[1].size));
		((void(*)(void))elfHeader->entry)();
		pageFree(fileSize);
	}
}
