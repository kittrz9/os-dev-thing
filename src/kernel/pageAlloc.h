#ifndef PAGEALLOC_H
#define PAGEALLOC_H

#include <stdint.h>

void pageAllocInit(void);

void* pageAlloc(uint32_t pageCount);
void pageFree(void* ptr);

#endif
