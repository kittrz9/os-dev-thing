#include "syscalls.h"

#include "serial.h"
#include "term.h"
#include "string.h"
#include "keyboard.h"
#include "pageAlloc.h"
#include "fs.h"

uint32_t* handleSyscalls(uint32_t regs[6]) {
	switch(regs[0]) {
		case 0: {
			char* str = (char*)regs[1];
			// ecx has the length of the string, or 0 if its null terminated
			size_t length = regs[2];
			if(length == 0) {
				length = strlen(str);
			}
			for(size_t i = 0; i < length; ++i) {
				putc(str[i]);
			}
			break;
		}
		case 1:
			// maybe could be made to wait until a valid key is returned like how the read syscall on linux works
			// so that programs don't need to continuously check for 0
			regs[1] = readKey();
			break;
		case 2:
			regs[1] = (uint32_t)pageAlloc(regs[1]);
			break;
		case 3:
			pageFree(regs[1]);
			break;
		case 4:
			size_t fileSize = getFileSize((char*)regs[1]);
			if(fileSize == 0) {
				regs[1] = 0;
				break;
			}
			uint8_t* buffer = pageAlloc(fileSize);
			readFile((char*)regs[1], buffer);
			regs[1] = (uint32_t)buffer;
			regs[2] = fileSize;
			break;
		case 5:
			writeFile((char*)regs[1], (uint8_t*)regs[2], regs[3]);
			break;
		default:
			serialWriteStr("unknown syscall: ");
			serialWriteHex32(regs[0]);
			serialWriteChar('\n');
			asm("cli;hlt");
	}
	return regs;
}
