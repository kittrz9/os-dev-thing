#include "syscalls.h"

#include "serial.h"
#include "term.h"
#include "string.h"

uint32_t returnRegs[6];

uint32_t* handleSyscalls(uint32_t regs[6]) {
	memcpy(returnRegs, regs, sizeof(returnRegs));
	switch(regs[0]) {
		case 0:
			puts((char*)regs[1]);
			break;
		default:
			serialWriteStr("unknown syscall: ");
			serialWriteHex32(regs[0]);
			serialWriteChar('\n');
			asm("cli;hlt");
	}
	return returnRegs;
}
