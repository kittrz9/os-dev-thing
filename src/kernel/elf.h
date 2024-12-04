#ifndef ELF_H
#define ELF_H

#include <stdint.h>

typedef struct {
	uint8_t magic[4];
	uint8_t bits;
	uint8_t endianness;
	uint8_t elfVersion;
	uint8_t abi;
	uint8_t abiVer;
	uint8_t padding[7];
	uint16_t type;
	uint16_t arch;
	uint32_t elfVersion2;
	uint32_t entry;
	uint32_t programHeadersOffset;
	uint32_t sectionHeadersOffset;
	uint32_t flags;
	uint16_t fileHeaderSize;
	uint16_t programHeaderSize;
	uint16_t programHeaderCount;
	uint16_t sectionHeaderSize;
	uint16_t sectionHeaderCount;
	uint16_t sectionNamesIndex;
} elfFileHeader;

typedef struct {
	uint32_t type;
	uint32_t fileOffset;
	uint32_t virtAddr;
	uint32_t physAddr;
	uint32_t size;
	uint32_t memSize;
	uint32_t flags;
	uint32_t align;
} elfProgramHeader;

typedef struct {
	uint32_t nameIndex;
	uint32_t type;
	uint32_t flags;
	uint32_t virtAddr;
	uint32_t fileOffset;
	uint32_t size;
	uint32_t link;
	uint32_t info;
	uint32_t align;
	uint32_t entSize;
} elfSectionHeader;

#endif // ELF_H
