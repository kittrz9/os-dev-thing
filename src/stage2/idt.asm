
section .data
align 4
idtr:
	dw idtEnd-idt-1; size
	dd idt ; offset (32 bit)

isrCount equ 255
isrFlags equ 10001110b

section .bss
align 4
idt:
%rep isrCount
	resw 1 ; offset low
	resw 1; segment
	resb 1 ; unused
	resb 1 ; flags
	resw 1 ; offset high
%endrep
idtEnd:

section .rodata
str:
	db "interrupt hit!!!!", 0xa, 0x0

extern serialWriteStr
section .text
align 4
interruptHandler:
	pushad
	sub esp, 4
	lea eax, str
	mov [esp], eax
	call serialWriteStr
	; acknowledge to PIC
	mov al, 0x20
	out 0x20, al
	in al, 0x60 ; discard scancode
	add esp, 4
	popad
	iret

section .rodata
scancodeStr:
		db "scancode: ", 0x0

extern serialWriteHex32
section .text
keyboardHandler:
	pushad
	sub esp, 4
	lea eax, scancodeStr
	mov [esp], eax
	call serialWriteStr
	xor eax, eax
	in al, 0x60
	mov [esp], eax
	call serialWriteHex32
	add esp, 4
	mov al, 0x20
	out 0x20, al
	popad
	iret

setIDTEntry:
	push ebp
	push eax
	push ecx
	push edi
	mov ebp, esp
	mov eax, [ebp+4+16]
	movzx ecx, byte [ebp+8+16]
	shl ecx, 3 ; multiply by 8
	lea edi, [idt+ecx]
	mov [edi], ax
	shr eax, 16
	mov [edi+6], ax
	mov eax, 0x008
	mov [edi+2], ax
	mov al, isrFlags
	mov [edi+5], al
	pop edi
	pop ecx
	pop eax
	pop ebp
	ret

global loadIDT
loadIDT:
	xor eax, eax
	sub esp, 12
	mov dword [esp], interruptHandler
isrLoop:
	mov dword [esp+4], eax
	call setIDTEntry
	inc eax
	cmp eax, isrCount
	jng isrLoop

	mov eax, 33
	mov dword [esp], keyboardHandler
	mov dword [esp+4], eax
	call setIDTEntry

	lidt [idtr]
	xchg bx, bx
	sti
	add esp, 12
	ret
