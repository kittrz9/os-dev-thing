#ifndef PAGEALLOC_H
#define PAGEALLOC_H

#include <stdint.h>

void* pageAlloc(uint32_t bytes);
void pageFree(uint32_t bytes);

#endif
