#ifndef PAGING_H
#define PAGING_H

#define VIRT_TO_PHYS(x) (x - 0x80000000)

#define BYTES_TO_PAGES(x) (x / 0x1000 + (x % 0x1000 != 0))

void mapPage(void* physAddr, void* virtAddr);

void mapPages(void* physAddr, void* virtAddr, uint16_t pageCount);

#endif // PAGING_H
