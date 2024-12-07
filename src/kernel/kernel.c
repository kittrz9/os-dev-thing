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

void loadIDT(void);

void kernel(void) {
	initSerial();

	serialWriteStr("kernel loaded at: ");
	serialWriteHex32((uint32_t)kernel);
	serialWriteStr("\n");

	serialWriteStr("waga baba bobo!!!! from the kernel!!!!\n");

	PICInit();

	uint8_t id = 0;
	do {
		PICSetMask(id);
		++id;
	} while(id != 0); // funny overflow moment
	PICClearMask(1); // keyboard

	loadIDT();

	/*mapPages((void*)0x1000000, (void*)0x401000, 0x10);
	*(uint8_t*)0x410000 = 0;*/

	/*extern uint32_t pageDir[256];
	uint32_t testPage = 0x401000;
	serialWriteStr("mapping page ");
	serialWriteHex32(testPage);
	serialWriteStr("...\n");
	mapPage((void*)0x1000000,(void*)testPage);
	serialWriteStr("page dir entry: ");
	serialWriteHex32((uint32_t)pageDir[testPage >> 22]);
	serialWriteStr("\n");
	serialWriteStr("page table entry: ");
	uint32_t pageTableAddr = pageDir[testPage >> 22] & 0xFFFFF000;
	uint32_t* pageTable = (uint32_t*)VIRT_TO_PHYS(pageTableAddr);
	serialWriteHex32(pageTable[(testPage >> 12) & 0xBFF]);
	serialWriteStr("\n");
	serialWriteStr("writing to page ");
	serialWriteHex32(testPage);
	serialWriteStr("...\n");
	*(int*)testPage = 0xAAAAAAAA;
	serialWriteStr("reading back from ");
	serialWriteHex32(testPage);
	serialWriteStr("...\n");
	serialWriteHex32(*(int*)testPage);
	serialWriteStr("\n");*/

	//timerSetFreq(2, TIMER_SQUARE2, 440);
	timerSetFreqDiv(0, TIMER_SQUARE2, 1194); // ~1ms
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

	// will eventually do this in a way that isn't garbage
	uint32_t fileSize = getFileSize("test.elf");
	uint8_t* buffer = pageAlloc(fileSize); 
	readFile("test.elf", buffer);
	elfFileHeader* elfHeader = (elfFileHeader*)buffer;
	elfProgramHeader* pHeaders = (elfProgramHeader*)(buffer + elfHeader->programHeadersOffset);
	elfSectionHeader* sHeaders = (elfSectionHeader*)(buffer + elfHeader->sectionHeadersOffset);
	//mapPage(VIRT_TO_PHYS(buffer), (void*)pHeaders[1].virtAddr);
	mapPages(VIRT_TO_PHYS(buffer), (void*)pHeaders[1].virtAddr, BYTES_TO_PAGES(pHeaders[1].size));
	serialWriteStr("calling file entry point\n");
	((void(*)(void))elfHeader->entry)();
	serialWriteStr("didn't die!!!!!\n");
	pageFree(fileSize);
	
	uint8_t hue = 0;
	while(1) {
		runShell();
		//sleep(20);
	}

	serialWriteStr("done\n");

	__asm__ volatile ("cli; hlt");
}
