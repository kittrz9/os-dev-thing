#ifndef STRING_H
#define STRING_H

#include <stddef.h>

int memcmp(const void* s1, const void* s2, size_t n);

int strcmp(const char* str1, const char* str2);

char* strcpy(char* restrict dst, const char* restrict src);

size_t strlen(const char* s);

#endif
