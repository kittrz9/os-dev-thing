#ifndef PAGING_H
#define PAGING_H

#define VIRT_TO_PHYS(x) (x - 0x80000000)

void mapPage(void* physAddr, void* virtAddr);
#endif // PAGING_H
