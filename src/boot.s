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

; https://wiki.osdev.org/Boot_Sequence#The_Traditional_Way
; boot partition will always be part 1
; stage2 of the bootloader will be on that boot partition

org 0x7c00
bits 16

global _start
_start:
	cli


	; set up stack
	mov sp, 0x7c00 ; value copied from limine since idk where to put it other than right before the boot code

	; set the screen to a pattern
	; just to see that it's working
	mov ah, 0x00
	mov al, 0x13
	int 0x10

	mov ch, 0x22
	mov cl, 0x20
	mov ax, 0xA000
	mov ds, ax
	mov di, 0
	mov ax, 0
fillScreen:
	mov byte ds:[di], ch
	inc ax
	cmp ax, 320
	jnz swapSkip
	xchg ch, cl
	xor ax, ax
swapSkip:
	xchg ch, cl
	inc di
	cmp di, 0xFA00
	jnz fillScreen

	jmp 0x00:initCS
initCS:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax


	; set up gdt
	lgdt [gdtr]
	; enter protected mode
	; https://wiki.osdev.org/Protected_Mode
	mov eax, cr0
	or al, 1
	mov cr0, eax
	jmp 0x08:reloadSegments
	bits 32
reloadSegments:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; set a20 line
	; fast a20 should be fine since I doubt I'll run this on anything that doesn't have it
	in al, 0x92
	test al, 2
	jnz a20skip
	or al, 2
	and al, 0xfe
	out 0x92, al
a20skip:


loop:
	jmp loop

gdtr:
	dw gdt-gdtEnd - 1 ; size
	dd gdt ; address
gdt:
	dw 0; limit
	dw 0; base low 2 bytes
	db 0; base mid byte
	db 0; access byte
	db 0; flags + limit again
	db 0; base high byte
	; code segment
	dw 0xffff; limit
	dw 0x0000; base low 2 bytes
	db 0x00; base mid byte
	db 10011011b; access byte
	db 11001111b ; flags + limit again
	db 0x00; base high byte
	; data segment
	dw 0xffff; limit
	dw 0x0000; base low 2 bytes
	db 0x00; base mid byte
	db 10010011b; access byte
	db 11001111b ; flags + limit again
	db 0x00; base high byte
gdtEnd:


times 0x1be-($-$$) db 0

; https://wiki.osdev.org/Partition_Table
; idk how cylinder head sector stuff works lmao
part1entry:
	db 0x80 ; boot flag
	db 0; starting head
	db 1; starting sector + highest 2 bits of start cylinder
	db 0; starting cylinder
	db 0x7f; system id
	db 0; ending head
	db 2; ending sector + highest 2 bits of end cylinder
	db 0; ending cylinder
	dd 0; relative sector
	dd 2; total sectors

part2entry:
	db 0 ; boot flag
	db 0; starting head
	db 0; starting sector + highest 2 bits of start cylinder
	db 0; starting cylinder
	db 0; system id
	db 0; ending head
	db 0; ending sector + highest 2 bits of end cylinder
	db 0; ending cylinder
	dd 0; relative sector
	dd 0; total sectors

part3entry:
	db 0 ; boot flag
	db 0; starting head
	db 0; starting sector + highest 2 bits of start cylinder
	db 0; starting cylinder
	db 0; system id
	db 0; ending head
	db 0; ending sector + highest 2 bits of end cylinder
	db 0; ending cylinder
	dd 0; relative sector
	dd 0; total sectors

part4entry:
	db 0 ; boot flag
	db 0; starting head
	db 0; starting sector + highest 2 bits of start cylinder
	db 0; starting cylinder
	db 0; system id
	db 0; ending head
	db 0; ending sector + highest 2 bits of end cylinder
	db 0; ending cylinder
	dd 0; relative sector
	dd 0; total sectors

global magic
magic:
	db 0x55, 0xAA

