#include "string.h"
#include <stdint.h>

int memcmp(const void* s1, const void* s2, size_t n) {
	const uint8_t* p1 = (uint8_t*)s1;
	const uint8_t* p2 = (uint8_t*)s2;
	for(size_t i = 0; i < n; ++i) {
		if(p1[i] != p2[i]) {
			return (p1[i] < p2[i] ? -1 : 1);
		}
	}
	return 0;
}

void* memcpy(const void* s1, const void* s2, size_t n) {
	uint8_t* p1 = (uint8_t*)s1;
	uint8_t* p2 = (uint8_t*)s2;
	for(size_t i = 0; i < n; ++i) {
		p1[i] = p2[i];
		++i;
	}
	return p1;
}

void* memset(const void* s, uint8_t c, size_t n) {
	uint8_t* p = (uint8_t*)s;
	for(size_t i = 0; i < n; ++i) {
		p[i] = c;
	}
	return p;
}

int strcmp(const char* str1, const char* str2) {
	size_t l1 = strlen(str1);
	size_t l2 = strlen(str2);

	// maybe doesn't return the correct value according to the standard
	// but I don't care since right now I'm just checking if it's returning 0
	if(l1 != l2) { return l1 - l2; }
	return memcmp(str1, str2, l1);
}

char* strcpy(char* restrict dst, const char* restrict src) {
	while(*src != '\0') {
		*dst++ = *src++;
	}
	*dst = '\0';
	return dst;
}

size_t strlen(const char* s) {
	size_t value = 0;
	while(*s != '\0') {
		++value;
		++s;
	}
	return value;
}
