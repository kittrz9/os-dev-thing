#ifndef FS_H
#define FS_H

#include <stdint.h>

typedef struct {
	char name[100];
	char mode[8];
	char ownerId[8];
	char groupId[8];
	char size[12];
	char modifyTime[12];
	char checksum[8];
	char typeFlag;
	char linkedFile[100];
	char ustarStr[5];
	char ustarVersion[2];
	char ownerName[32];
	char groupName[32];
	char devMajorNumber[8];
	char devMinorNumber[8];
	char prefix[155];
} ustarHeader;


extern uint32_t fsSize;
extern uint32_t fsLBA;

void initFS(void);

uint8_t readFile(char* name, uint8_t* dest);

uint32_t getFileSize(char* name);
uint32_t parseOctStr(char* str);

#endif
