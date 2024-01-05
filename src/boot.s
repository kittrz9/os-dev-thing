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

bits 16

section .bootstrap
global _start
_start:
	cli
	mov ah, 0x00
	mov al, 0x13
	int 0x10


	mov cl, 0
	mov ax, 0xA000
	mov ds, ax
	mov di, 0xFA00 ; 320x200 in hex
fillScreen:
	mov byte ds:[di], cl
	inc cl
	dec di
	or di, di
	jnz fillScreen
loop:
	jmp loop

section .magic
global magic
magic:
	db 0x55, 0xAA
