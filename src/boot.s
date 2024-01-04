; https://wiki.osdev.org/MBR_(x86)

; 0x000 - bootstrap
; 0x1B8 - signature, semi-unused
; 0x1BC - unused
; 0x1BE - partition table entry 1
; 0x1CE - partition table entry 2
; 0x1DE - partition table entry 3
; 0x1EE - partition table entry 4
; 0x1FE - magic number (0x55, 0xAA)

; there are currently no other partitions so no entries are currently set

section .bootstrap
global _start
_start:
	cli
	hlt
loop:
	jmp loop

section .magic
global magic
magic:
	db 0x55, 0xAA
