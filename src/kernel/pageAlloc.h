#ifndef PAGEALLOC_H
#define PAGEALLOC_H

#include <stdint.h>

void pageAllocInit();

uint8_t* pageAlloc(uint32_t pageCount);

#endif
