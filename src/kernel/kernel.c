#include <stddef.h>
#include <string.h>

#include "serial.h"
#include "io.h"
#include "screen.h"
#include "pic.h"
#include "timer.h"
#include "text.h"
#include "keyboard.h"
#include "term.h"
#include "ata.h"
#include "fs.h"
#include "files.h"
#include "pageAlloc.h"
#include "paging.h"
#include "elf.h"
#include "shell.h"
#include "tasks.h"

void loadIDT(void);

void kernelTask(void) {
	while(1) {
		runShell();
	}
	__asm__ volatile ("cli; hlt");
}
void task1(void) {
	while(1) {
		serialWriteStr("task 1!!!\n");
		sleep(1000);
	}
}
void task2(void) {
	while(1) {
		serialWriteStr("task 2!!!\n");
		sleep(500);
	}
}

void task3(void) {
	while(1) {
		drawTerm();
		sleep(20);
	}
}

void kernel(void) {
	initSerial();

	serialWriteStr("kernel loaded at: ");
	serialWriteHex32((uint32_t)kernel);
	serialWriteStr("\n");

	serialWriteStr("waga baba bobo!!!! from the kernel!!!!\n");

	PICInit();

	uint16_t id = 0;
	do {
		PICSetMask(id);
		++id;
	} while(id < 256);
	PICClearMask(1); // keyboard

	addTask(task1, 5);
	addTask(task2, 5);
	addTask(task3, 10);
	addTask(kernelTask, 10);
	
	loadIDT();


	//timerSetFreq(2, TIMER_SQUARE2, 440);
	timerSetFreqDiv(0, TIMER_RATE, 1194); // ~1ms
	PICClearMask(0); // timer
	/*uint8_t tmp = inb(0x61);
	if(tmp != (tmp|3)){
		outb(0x61, tmp | 3);
	}*/

	serialWriteStr("framebuffer loaded at: ");
	serialWriteHex32((uint32_t)vbeInfo.framebuffer);
	serialWriteStr("\n");

	initScreen();
	initTerm();

	puts("https://kittrz.gay/\n");

	if(!initATA()) {
		initFS();
		listFiles();
		puts("reading TODO.md\n\n");
		printFile("TODO.md");
	}

	serialWriteStr("unblocking tasks\n");
	tasksBlocked = 0;
	while(1) {}
}

