#ifndef PAGEALLOC_H
#define PAGEALLOC_H

#include <stdint.h>

void* pageAlloc(uint32_t pageCount);
void pageFree(void);

#endif
