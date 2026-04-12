#ifndef PAGEALLOC_H
#define PAGEALLOC_H

#include <stddef.h>

void* pageAlloc(size_t bytes);
void pageFree(void* p, size_t bytes);

#endif
