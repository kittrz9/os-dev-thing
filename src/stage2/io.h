#ifndef IO_H
#define IO_H

#include <stdint.h>

// https://wiki.osdev.org/Inline_Assembly/Examples#I.2FO_access

static inline void outb(uint16_t port, uint8_t value) {
	__asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

static inline uint8_t inb(uint16_t port) {
	uint8_t ret;
	__asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

static inline void ioWait(void) {
	outb(0x80, 0);
}

#endif
