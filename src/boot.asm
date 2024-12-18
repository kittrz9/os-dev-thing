; https://wiki.osdev.org/MBR_(x86)

; 0x000 - bootstrap
; 0x1B8 - signature, semi-unused
; 0x1BC - unused
; 0x1BE - partition table entry 1
; 0x1CE - partition table entry 2
; 0x1DE - partition table entry 3
; 0x1EE - partition table entry 4
; 0x1FE - magic number (0x55, 0xAA)

; stage 2 at partition table 1

; https://wiki.osdev.org/Boot_Sequence#The_Traditional_Way
; boot partition will always be part 1
; stage2 of the bootloader will be on that boot partition

%macro bochs_brk 0
	xchg bx, bx
%endmacro

fbaddr equ 0x1000
stage2loc equ 0xc0000

; stage2size and fssize defined when assembling in build.sh

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

	mov ax, 0x4f00
	mov bx, 0x0000
	mov es, bx
	mov di, 0x7e00
	int 0x10
	cmp ax, 0x004f
	je getVesaMode
	mov ax, 0xA000
	mov ds, ax
	mov byte ds:[0], 2
	jmp loop

getVesaMode:
	mov ax, 0x4f01
	mov cx, 0x4112
	mov bx, fbaddr
	mov di, bx
	int 0x10

setVesaMode:
	mov ax, 0x4f02
	mov bx, 0x4112
	int 0x10
	cmp ax, 0x004f
	je vesaDone
	mov ax, 0xA000
	mov ds, ax
	mov byte ds:[0], 4
	jmp loop
vesaDone:

	xor bx, bx
	mov ds, bx
	mov es, bx
	cld
	mov ah, 0x02
	mov al, stage2size
	mov ch, 0
	mov cl, 2
	mov dh, 0
	mov bx, (stage2loc & 0xFF0000) >> 4
	mov es, bx
	mov bx, (stage2loc & 0xFFFF)
	int 0x13

	; I think this part and the other part that reloads segments are basically also from seeing how limine does this and basically copying
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

	mov eax, fbaddr
	push eax
	call stage2loc

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


times 0x1fe-($-$$) db 0

global magic
magic:
	db 0x55, 0xAA

