#include "fs.h"
#include <stddef.h>
#include "string.h"
#include "ata.h"
#include "mbr.h"
#include "serial.h"

// https://wiki.osdev.org/SFS
// https://web.archive.org/web/20090923015653/http://dimensionalrift.homelinux.net/combuster/vdisk/sfs.html#Super-Block

uint32_t fsSize;
uint32_t fsLBA;
uint32_t indicesLBA;
uint32_t dataBlocks;
uint32_t indicesBytes;

void initFS(void) {
	uint8_t buffer[512];
	readATA(0, 1, (uint16_t*)buffer);
	mbrPartition* fsPart = (mbrPartition*)(buffer+PARTITION2_OFFSET);

	fsSize = fsPart->size;
	fsLBA = fsPart->lba-1;
	readATA(fsLBA, 1, (uint16_t*)buffer);

	if(memcmp(&buffer[0x1ac], "SFS", 3) != 0) {
		serialWriteStr("invalid sfs superblock\n");
		fsSize = 0;
		fsLBA = 0;
		return;
	}
	indicesLBA = fsLBA + fsSize - 1;
	dataBlocks = *(uint32_t*)(buffer+0x19c);
	indicesBytes = *(uint32_t*)(buffer+0x1a4);
	serialWriteStr("data blocks: ");
	serialWriteHex32(dataBlocks);
	serialWriteChar('\n');
	/*readATA(indicesLBA, 1, (uint16_t*)buffer);
	serialWriteStr(&buffer[0x1a2]);
	serialWriteChar('\n');*/
	/*ustarHeader* header = (ustarHeader*)buffer;
	if(memcmp(header->ustarStr, "ustar", 5) != 0) {
		fsSize = 0;
		fsLBA = 0;
		serialWriteStr("invalid filesystem\n");
	}*/
}

uint32_t getFileSize(char* name) {
	uint8_t buffer[512];

	if(fsSize == 0) {
		serialWriteStr("file system not initialized or invalid\n");
		return 0;
	}

	uint32_t currentLBA = indicesLBA;

	readATA(currentLBA, 1, (uint16_t*)buffer);

	uint8_t* entry = &buffer[512 - 64];

	while(*entry != 0 && entry >= buffer) {
		//serialWriteHex32(*entry);
		if(*entry == 0x12) {
			//serialWriteStr(entry+0x22);
			if(strcmp(entry+0x22, name) == 0) {
				return *(uint32_t*)(entry+0x1a);
			}
		}
		entry -= 64;
		if(entry < buffer) {
			--currentLBA;
			readATA(currentLBA, 1, (uint16_t*)buffer);
			entry = &buffer[512-64];
		}
	}

	/*for(uint32_t i = fsLBA; i < fsLBA+fsSize; ++i) {
		readATA(i, 1, (uint16_t*)buffer);
		ustarHeader* header = (ustarHeader*)buffer;
		if(memcmp(header->ustarStr, "ustar", 5) == 0) {
			uint32_t fileSize = parseOctStr(header->size);
			if(strcmp(header->name, name) == 0) {
				return fileSize;
			} else {
				i += fileSize/512 + (fileSize%512!=0);
			}
		}
	}*/
	return 0;
}

uint8_t readFile(char* name, uint8_t* dest) {
	uint8_t buffer[512];
	if(fsSize == 0) {
		serialWriteStr("file system not initialized or invalid\n");
		return 0;
	}

	uint32_t currentLBA = indicesLBA;

	readATA(currentLBA, 1, (uint16_t*)buffer);

	uint8_t* entry = &buffer[512 - 64];

	while(*entry != 0) {
		//serialWriteHex32(*entry);
		if(*entry == 0x12) {
			//serialWriteStr(entry+0x22);
			if(strcmp(entry+0x22, name) == 0) {
				/*serialWriteStr("found file ");
				serialWriteStr(name);
				serialWriteChar('\n');*/
				uint64_t startBlock = *(uint64_t*)(entry+0xa);
				uint64_t blockCount = *(uint64_t*)(entry+0x12) - startBlock;
				uint64_t startLBA = fsLBA + startBlock;
				//serialWriteHex32(blockCount);
				readATA(startLBA, blockCount, (uint16_t*)dest);
				return 1;
			}
		}
		entry -= 64;
		if(entry < buffer) {
			--currentLBA;
			readATA(currentLBA, 1, (uint16_t*)buffer);
			entry = &buffer[512-64];
		}
	}

	/*for(uint32_t i = fsLBA; i < fsLBA+fsSize; ++i) {
		readATA(i, 1, (uint16_t*)buffer);
		ustarHeader* header = (ustarHeader*)buffer;
		if(memcmp(header->ustarStr, "ustar", 5) == 0) {
			uint32_t fileSize = parseOctStr(header->size);
			if(strcmp(header->name, name) == 0) {
				readATA(i+1, fileSize/512 + (fileSize%512!=0), (uint16_t*)dest);
				return 1;
			} else {
				i += fileSize/512 + (fileSize%512!=0);
			}
		}
	}*/
	return 0;
}

void writeFile(char* name, uint8_t* fileBuffer, size_t fileSize) {
	uint8_t buffer[512];
	if(fsSize == 0) {
		serialWriteStr("file system not initialized or invalid\n");
		return;
	}

	uint32_t currentLBA = indicesLBA;

	readATA(currentLBA, 1, (uint16_t*)buffer);

	uint8_t* entry = &buffer[512 - 64];

	while(*entry != 0 && *entry != 1) {
		if(*entry == 0x12) {
			if(strcmp(entry+0x22, name) == 0) {
				break;
			}
		}
		entry -= 64;
		if(entry < buffer) {
			--currentLBA;
			readATA(currentLBA, 1, (uint16_t*)buffer);
			entry = &buffer[512-64];
		}
	}

	uint32_t startBlock = 0;
	uint32_t newBlockCount = fileSize/512 + (fileSize % 512 == 0 ? 0 : 1);
	if(*entry == 1) {
		// honestly not sure why I'm bothering with the volume info stuff
		// I could probably just make a filesystem similar to sfs without most of the stuff to simplify things even more
		// since I'm not gonna use most of it lmao
		if(entry == buffer) {
			uint8_t volumeInfo[64];
			memcpy(volumeInfo, entry, 64);
			readATA(currentLBA-1, 1, (uint16_t*)buffer);
			memcpy(&buffer[512-64], volumeInfo, 64);
			writeATA(currentLBA-1, 1, (uint16_t*)buffer);
			readATA(currentLBA, 1, (uint16_t*)buffer);
		} else {
			memcpy(entry - 64, entry, 64);
		}
		*entry = 0x12;
		strcpy(entry+0x22, name);
	} else {
		startBlock = *(uint64_t*)(entry+0xa);
		if(*(uint64_t*)(entry+0x1a) >= fileSize) {
			writeATA(fsLBA + startBlock, newBlockCount, (uint16_t*)fileBuffer);
			*(uint64_t*)(entry+0x1a) = fileSize;
			*(uint64_t*)(entry+0x12) = startBlock + newBlockCount;
			writeATA(currentLBA, 1, (uint16_t*)buffer);
			return;
		}
	}
	// ideally should try to find unused space in the data area by like looping over the entries and seeing where files aren't
	// but this should work for now
	startBlock = dataBlocks + 1; // counting the superblock
	dataBlocks += newBlockCount;
	writeATA(fsLBA + startBlock, newBlockCount, (uint16_t*)fileBuffer);

	// write file info
	*(uint64_t*)(entry+0x1a) = fileSize;
	*(uint64_t*)(entry+0xa) = startBlock;
	*(uint64_t*)(entry+0x12) = startBlock + newBlockCount;
	writeATA(currentLBA, 1, (uint16_t*)buffer);

	// update superblock
	readATA(fsLBA, 1, (uint16_t*)buffer);
	*(uint64_t*)(buffer+0x19c) = dataBlocks;
	writeATA(fsLBA, 1, (uint16_t*)buffer);

	return;
}
