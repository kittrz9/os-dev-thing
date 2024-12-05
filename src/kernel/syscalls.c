#include "syscalls.h"

#include "serial.h"
#include "term.h"

void handleSyscalls(uint32_t regs[6]) {
	switch(regs[0]) {
		case 0:
			puts((char*)regs[1]);
			return;
		default:
			serialWriteStr("unknown syscall: ");
			serialWriteHex32(regs[0]);
			serialWriteChar('\n');
			asm("cli;hlt");
	}
}
