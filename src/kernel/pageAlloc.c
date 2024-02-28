#include "pageAlloc.h"
#include <stddef.h>
#include "serial.h"

// this talks about virtual memory managment but I think it'd probably work for this too
// https://wiki.osdev.org/Page_Frame_Allocation#Flat_List

typedef struct pageHeader_t {
	struct pageHeader_t* next;
} pageHeader;

extern void* endPage;

pageHeader* firstPage = (pageHeader*)&endPage; // endPage defined by linker

void pageAllocInit() {
	firstPage->next = NULL;

	return;
}

uint8_t* pageAlloc(uint32_t bytes) {
	pageHeader* currentPage = firstPage;

	while(currentPage->next != NULL) {
		currentPage = currentPage->next;
	}

	currentPage->next = currentPage+bytes+sizeof(pageHeader);
	// have to cast to an int so it doesn't do full pointer math
	// the pageHeader* cast is so gcc doesn't throw a warning
	currentPage->next = (pageHeader*)((uint32_t)(currentPage->next) + 0x1000 - ((uint32_t)(currentPage->next) & 0xFFF)); // align to 4k


	currentPage->next->next = NULL;

	return (uint8_t*)currentPage+sizeof(pageHeader);
}

