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

int strcmp(const char* str1, const char* str2) {
	size_t i = 0;
	while(str1[i] != '\0' && str2[i] != '\0') {
		if(str1[i] != str2[i]) {
			return (str1[i] < str2[i] ? -1 : 1);
		}
	}
	return 0;
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
