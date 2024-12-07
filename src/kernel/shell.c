#include "shell.h"

#include "keyboard.h"
#include "term.h"
#include "string.h"
#include "elf.h"
#include "pageAlloc.h"
#include "paging.h"
#include "fs.h"

char cmdBuffer[64];

void runShell(void) {
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
	if(loadElf(cmdBuffer) == NULL) {
		puts("could not find program \"");
		puts(cmdBuffer);
		puts("\"\n");
	} else {
		launchElf();
		freeElf();
	}
}
