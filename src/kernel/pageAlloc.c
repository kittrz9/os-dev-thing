#include "pageAlloc.h"
#include <stddef.h>

// this talks about virtual memory managment but I think it'd probably work for this too
// https://wiki.osdev.org/Page_Frame_Allocation#Flat_List

typedef struct pageHeader_t {
	struct pageHeader_t* next;
	uint8_t used;
	uint32_t size;
} pageHeader;

extern void* endPage;

pageHeader* firstPage = (pageHeader*)&endPage; // endPage defined by linker

void pageAllocInit(void) {
	firstPage->next = NULL;
	firstPage->used = 0;
	firstPage->size = 0;

	return;
}

void* pageAlloc(uint32_t bytes) {
	pageHeader* currentPage = firstPage;

	while((currentPage->used != 0 || currentPage->size < bytes) && currentPage->next != NULL) {
		currentPage = currentPage->next;
	}

	currentPage->next = (pageHeader*)((uint32_t)(currentPage)+bytes+sizeof(pageHeader));
	// have to cast to an int so it doesn't do full pointer math
	// the pageHeader* cast is so gcc doesn't throw a warning
	currentPage->next = (pageHeader*)((uint32_t)(currentPage->next) + 0x1000 - ((uint32_t)(currentPage->next) & 0xFFF)); // align to 4k
	currentPage->used = 1;
	currentPage->size = bytes;


	currentPage->next->next = NULL;
	currentPage->next->used = 0;
	currentPage->next->size = 0;

	return (uint8_t*)currentPage+sizeof(pageHeader);
}

void pageFree(void* ptr) {
	pageHeader* currentPage = (pageHeader*)((uint8_t*)ptr - sizeof(pageHeader));

	currentPage->used = 0;
}

