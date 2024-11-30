#include "pageAlloc.h"
#include <stddef.h>

#include "serial.h"

extern void* endPage;

typedef struct {
	void* addr;
	uint32_t pages;
} pageStackEntry;

#define PAGE_STACK_SIZE 256

pageStackEntry pageStack[PAGE_STACK_SIZE];
uint32_t pageStackPointer;

uint32_t pagesAllocated;

void* pageAlloc(uint32_t bytes) {
	uint32_t newPages = bytes / 0x1000 + (bytes % 0x1000 != 0);
	uint32_t returnAddr = (uint32_t)&endPage + (pagesAllocated * 0x1000);

	pageStack[pageStackPointer].addr = (void*)returnAddr;
	pageStack[pageStackPointer].pages = bytes;
	++pageStackPointer;

	pagesAllocated += newPages;

	return (void*)returnAddr;
}

void pageFree(void) {
	--pageStackPointer;
	pagesAllocated -= pageStack[pageStackPointer].pages;
}

