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
		listFiles();
	}

	// will eventually do this in a way that isn't garbage
	uint32_t fileSize = getFileSize("test.elf");
	uint8_t* buffer = pageAlloc(fileSize); 
	readFile("test.elf", buffer);
	elfFileHeader* elfHeader = (elfFileHeader*)buffer;
	elfProgramHeader* pHeaders = (elfProgramHeader*)(buffer + elfHeader->programHeadersOffset);
	elfSectionHeader* sHeaders = (elfSectionHeader*)(buffer + elfHeader->sectionHeadersOffset);
	mapPage(VIRT_TO_PHYS(buffer), (void*)pHeaders[1].virtAddr);
	serialWriteStr("calling file entry point\n");
	((void(*)(void))elfHeader->entry)();
	serialWriteStr("didn't die!!!!!\n");
	
	uint8_t hue = 0;
	while(1) {
		uint32_t color = hueToRgb(hue);
		// assuming color format, cringe but works in qemu for now lmao
		uint8_t b = (color&0xff);
		uint8_t g = (color&0xff00)>>8;
		uint8_t r = (color&0xff0000)>>16;
		uint8_t* ptr = backBuffer;
		uint16_t pitch = vbeInfo.pitch;
		for(uint16_t line = 0; line < 480; ++line) {
			for(uint16_t i = 0; i < 640*3; i+=3) {
				*(ptr+i) = b;
				*(ptr+i+1) = g;
				*(ptr+i+2) = r;
			}
			ptr += pitch;
		}
		++hue;

		// should ideally be checking for if it returns null but putc ignores null bytes
		putc(readKey());

		drawTerm();

		refreshScreen();

		sleep(20);

	}

	serialWriteStr("done\n");

	__asm__ volatile ("cli; hlt");
}
