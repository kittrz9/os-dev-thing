#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

int memcmp(const void* s1, const void* s2, size_t n);

void* memcpy(const void* s1, const void* s2, size_t n);

void* memset(const void* s, uint8_t c, size_t n);

int strcmp(const char* str1, const char* str2);

char* strcpy(char* restrict dst, const char* restrict src);

size_t strlen(const char* s);

#endif
