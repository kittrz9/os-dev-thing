#include "pageAlloc.h"
#include <stddef.h>

#include "serial.h"

extern void* endPage;

static uint32_t pagesAllocated = 0;

void* pageAlloc(uint32_t bytes) {
	uint32_t newPages = bytes / 0x1000 + (bytes % 0x1000 != 0);
	uint32_t returnAddr = ((uint32_t)&endPage) + (pagesAllocated * 0x1000);

	pagesAllocated += newPages;

	return (void*)returnAddr;
}

void pageFree(uint32_t bytes) {
	pagesAllocated -= bytes / 0x1000 + (bytes % 0x1000 != 0);
}

