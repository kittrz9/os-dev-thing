
section .data
align 4
idtr:
	dw idtEnd-idt-1; size
	dd idt ; offset (32 bit)

isrCount equ 255

align 4
idt:
%rep isrCount
	dw 0x0000 ; offset low
	dw 0x0008; segment
	db 0x00 ; unused
	db 10001110b ; present bit, DPL(2 bits), 0, gate type (4 bits)
	dw 0x0000; offset high
%endrep
idtEnd:

section .rodata
str:
	db "interrupt hit!!!!", 0xa, 0x0

extern serialWriteStr
section .text
align 4
interruptHandler:
	cli
	lea eax, str
	mov [esp], eax
	call serialWriteStr
loop:
	hlt
	jmp loop

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
	pop edi
	pop ecx
	pop eax
	pop ebp
	ret

global loadIDT
loadIDT:
	xchg bx, bx
	mov eax, 0
	sub esp, 12
	mov dword [esp], interruptHandler
isrLoop:
	mov dword [esp+4], eax
	call setIDTEntry
	inc eax
	cmp eax, isrCount
	jng isrLoop
	lidt [idtr]
	xchg bx, bx
	sti
	add esp, 12
	ret
