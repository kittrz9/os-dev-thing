#include "shell.h"

#include "keyboard.h"
#include "term.h"
#include "string.h"
#include "elf.h"
#include "pageAlloc.h"
#include "paging.h"
#include "fs.h"
#include "tasks.h"

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
		// having it like this doesn't do anything right now
		// but would probably be needed if I end up doing stuff like letting tasks end other tasks since then they'd not be able to return normally
		// or if I end up implementing stuff to handle if a task ends up hitting a page fault or something
		waitTask(addTask(launchElf, 5));
		freeElf();
	}
}
