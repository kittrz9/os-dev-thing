#include "pageAlloc.h"
#include <stddef.h>

#include "serial.h"

extern void* endPage;

static uint32_t pagesAllocated = 0;

uint32_t pagesBitmap[0x1000]; // 16k to address 64m

void* pageAlloc(size_t bytes) {
	/*serialWriteStr("PAGE ALLOC\nsize: ");
	serialWriteHex32(bytes);
	serialWriteChar('\n');*/
	uint32_t pageCount = bytes/0x1000;
	if(pageCount == 0) { pageCount = 1; }
	// probably should be using paging stuff to not need to find a perfectly contiguous region of memory but whatever
	uint32_t allocationBit = 0;
	uint8_t pagesFound = 0;
	while(!pagesFound) {
		// I hate C's order of operations with anything bit related
		while(((pagesBitmap[allocationBit/32] >> (allocationBit%32)) & 1) != 0) {
			++allocationBit;
		}
		for(uint32_t i = 0; i < pageCount; ++i) {
			if(((pagesBitmap[(allocationBit+i)/32] >> ((allocationBit+i)%32)) & 1) != 0) {
				allocationBit += i;
				break;
			}
		}
		pagesFound = 1;
	}
	if(allocationBit > 0x1000*32) {
		serialWriteStr("out of memory!!!\n");
		__asm__ volatile("cli;hlt");
	}
	for(uint32_t i = 0; i < pageCount; ++i) {
		pagesBitmap[(allocationBit+i)/32] |= (1<<((allocationBit+i)%32));
	}
	/*serialWriteStr("return: ");
	serialWriteHex32(((uint32_t)&endPage + (allocationBit*0x1000)));
	serialWriteChar('\n');*/
	return (void*)((uint32_t)&endPage + (allocationBit*0x1000));
}

void pageFree(void* p, size_t bytes) {
	/*serialWriteStr("PAGE FREE\nptr: ");
	serialWriteHex32((uint32_t)p);
	serialWriteStr("\nsize: ");
	serialWriteHex32(bytes);
	serialWriteChar('\n');*/
	uint32_t pageCount = bytes/0x1000;
	if(pageCount == 0) { pageCount = 1; }
	uint32_t allocationBit = ((uint32_t)p - (uint32_t)&endPage)/0x1000;
	for(uint32_t i = 0; i < pageCount; ++i) {
		pagesBitmap[(allocationBit+i)/32] &= ~(1<<((allocationBit+i)%32));
		++allocationBit;
	}
}

/*void* pageAlloc(uint32_t bytes) {
	uint32_t newPages = bytes / 0x1000 + (bytes % 0x1000 != 0);
	uint32_t returnAddr = ((uint32_t)&endPage) + (pagesAllocated * 0x1000);

	pagesAllocated += newPages;

	return (void*)returnAddr;
}

void pageFree(uint32_t bytes) {
	pagesAllocated -= bytes / 0x1000 + (bytes % 0x1000 != 0);
}*/

