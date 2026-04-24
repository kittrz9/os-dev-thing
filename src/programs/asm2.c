#include <stdint.h>
#include <stddef.h>

// really need to move these to some sort of standard library
void sysPrint(char* str, uint32_t length) {
	__asm__ volatile("int $0x80" : : "a" (0), "b" (str), "c" (length) : "memory");
}

char sysReadKey(char* str, uint32_t length) {
	char c = 0;
	__asm__ volatile("int $0x80" : "=b" (c) : "a" (1) : "memory");
	return c;
}

void* sysAlloc(uint32_t size) {
	void* p = NULL;
	__asm__ volatile("int $0x80" : "=b" (p) : "a" (2), "b" (size) : "memory");
	return p;
}

void sysFree(void* p, uint32_t size) {
	__asm__ volatile("int $0x80" : : "a" (3), "b" (p), "c" (size) : "memory");
}

void* sysReadFile(char* fileName, uint32_t* sizePtr) {
	uint32_t size = 0;
	void* p = NULL;
	__asm__ volatile("int $0x80" : "=b" (p), "=c" (size) : "a" (4), "b" (fileName) : "memory");
	*sizePtr = size;
	return p;
}

void sysWriteFile(char* fileName, uint32_t size, void* buffer) {
	__asm__ volatile("int $0x80" : : "a" (5), "b" (fileName), "c" (buffer), "d" (size) : "memory");
}

struct {
	char* name;
	uint8_t* bytes;
	uint32_t byteCount;
	uint8_t argCount; // need to figure out how I should handle args
} instructions[] = {
	{ "ret", (uint8_t[]){ 0xc3 }, 1, 0},
	{ "cli", (uint8_t[]){ 0xfa }, 1, 0},
	{ "hlt", (uint8_t[]){ 0xf4 }, 1, 0},
	{ "sti", (uint8_t[]){ 0xfb }, 1, 0},
	// dealing with stuff like all the mov varients seems horrible lmao
	// could maybe have multiple arrays of instructions that each take specific arguments and only iterate through those when parsing them
};


// stuff in bss probably gets set to 0 since it's all put into .text
uint8_t* program;
uint32_t programSize;

void addByte(uint8_t byte) {
	program[programSize] = byte;
	++programSize;
}

void addBytes(uint8_t* bytes, uint32_t byteCount) {
	uint8_t* p = program + programSize;
	programSize += byteCount;
	while(byteCount != 0) {
		*p = *bytes;
		++p;
		++bytes;
		--byteCount;
	}
}

// could rename this to addWord or rename addByte to addU8 to keep consistency
void addU16(uint16_t data) {
	addBytes((uint8_t*)&data, 2);
}

void addU32(uint32_t data) {
	addBytes((uint8_t*)&data, 4);
}

// should probably add string.h
int strcmp(char* str1, char* str2) {
	// not gonna bother with correct return values, 0 if they're equal 1 if they're not
	do {
		if(*str1 != *str2) { return 1;}
		++str1;
		++str2;
	} while(*str1 != '\0' && *str2 != '\0');
	return 0;
}

void parseFile(char* fileBuffer, uint32_t fileSize) {
	static char lineBuffer[64];
	char* filePtr = fileBuffer;

	while(*filePtr != '\0') {
		while(*filePtr == ' ' || *filePtr == '\t' || *filePtr == '\n') {
			++filePtr;
		}

		char* bufferPtr = lineBuffer;
		while(*filePtr != '\n' && *filePtr != '\0') {
			*bufferPtr = *filePtr;
			++bufferPtr;
			++filePtr;
		}
		*bufferPtr = '\0';

		for(uint32_t i = 0; i < sizeof(instructions)/sizeof(instructions[0]); ++i) {
			if(strcmp(lineBuffer, instructions[i].name) == 0) {
				sysPrint(instructions[i].name, 0);
				addBytes(instructions[i].bytes, instructions[i].byteCount);
				break;
			}
		}
		lineBuffer[0] = '\0';
	}
}

void entry(void) {
	uint32_t fileSize = 0;
	char* fileBuffer = sysReadFile("test.asm", &fileSize);
	if(fileBuffer == NULL) { 
		sysPrint("could not find test.asm\n", 0);
		return; 
	}

	#define MAX_PROGRAM_SIZE 0x4000
	program = sysAlloc(MAX_PROGRAM_SIZE);
	programSize = 0;


#define VIRTUAL_ADDR 0x40000
	// header
	// would probably be a better idea to just have a whole premade header set up as an array of bytes and just adding that and modifying it later
	addBytes((uint8_t*)"\x7F""ELF", 4);
	addByte(1); // 32 bit
	addByte(1); // little endian
	addByte(1); // header version
	addByte(0); // abi
	programSize += 8; // padding
	addU16(2); // executable
	addU16(3); // x86
	addU32(1); // elf version
	uint32_t* entryPoint = (uint32_t*)(program+programSize);
	programSize += 4;
	addU32(64 /* elf header size */); // program header offset
	uint32_t* sectionHeaderOffset = (uint32_t*)(program+programSize);
	programSize += 4;
	programSize += 4; // flags
	addU16(64); // header size
	addU16(32); // program header size
	addU16(2); // program header count
	addU16(32); // section header size
	addU16(0); // section header count (kernel doesn't use section headers yet, so I'm not gonna bother for now)
	addU16(0); // section index

	// program header
	programSize = 64;
	addU32(0); // type (null)
	addU32(0); // offset
	addU32(0); // virtual addr
	programSize += 4; // physical addr (unused)
	//uint32_t* codeSize = (uint32_t*)(program+programSize);
	programSize += 4;
	programSize += 4; // mem size (unused)
	addU32(0); // flags (read, write, exec)
	addU32(0); // alignment (unused)

	programSize = 64+32;
	addU32(1); // type (load)
	addU32(0); // offset
	addU32(VIRTUAL_ADDR); // virtual addr
	programSize += 4; // physical addr (unused)
	uint32_t* codeSize = (uint32_t*)(program+programSize);
	programSize += 4;
	programSize += 4; // mem size (unused)
	addU32(1|2|4); // flags (read, write, exec)
	addU32(32); // alignment (unused)

	programSize = 64+64;
	*entryPoint = VIRTUAL_ADDR + programSize;
	parseFile(fileBuffer, fileSize);

	*codeSize = programSize;

	//addBytes((uint8_t[]){ 0, 1, 2 }, 3);
	sysWriteFile("program", programSize, program);
	sysFree(program, MAX_PROGRAM_SIZE);

	sysFree(fileBuffer, fileSize);
	return;
}
