#include "elf.h"

#include <stddef.h>

#include "fs.h"
#include "pageAlloc.h"
#include "paging.h"

size_t elfAllocatedPages;
void (*loadedElfEntry)(void);

void* loadElf(char* fileName) {
	uint32_t fileSize = getFileSize(fileName);
	if(fileSize == 0) {
		return NULL;
	}
	uint8_t* buffer = pageAlloc(fileSize); 
	readFile(fileName, buffer);
	elfFileHeader* elfHeader = (elfFileHeader*)buffer;
	elfProgramHeader* pHeaders = (elfProgramHeader*)(buffer + elfHeader->programHeadersOffset);
	elfSectionHeader* sHeaders = (elfSectionHeader*)(buffer + elfHeader->sectionHeadersOffset);
	// hard coded to load the second program header that just has everything in it
	// should probably be fixed
	(void)sHeaders; // unused
	mapPages(VIRT_TO_PHYS(buffer), (void*)pHeaders[1].virtAddr, BYTES_TO_PAGES(pHeaders[1].size));
	loadedElfEntry = ((void(*)(void))elfHeader->entry);
	return buffer;
}

void launchElf(void) {
	loadedElfEntry();
}

void freeElf(void) {
	pageFree(elfAllocatedPages);
}
