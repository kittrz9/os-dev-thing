
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
interruptStr:
	db "interrupt hit!!!!", 0xa, 0x0

extern serialWriteStr
section .text
align 4
interruptHandler:
	pushad
	sub esp, 4
	lea eax, interruptStr
	mov [esp], eax
	call serialWriteStr
	; acknowledge to PIC
	mov al, 0x20
	out 0x20, al
	in al, 0x60 ; discard scancode
	add esp, 4
	popad
	iret

; https://wiki.osdev.org/Programmable_Interval_Timer#Using_the_IRQ_to_Implement_sleep
extern countDown
align 4
timerHandler:
	push eax
	mov eax, [countDown]
	test eax, eax
	jz timerDone
	dec eax
	mov [countDown], eax
timerDone:
	mov al, 0x20
	out 0x20, al
	pop eax
	iret

extern handleScancode
section .text
keyboardHandler:
	pushad
	sub esp, 4
	xor eax, eax
	in al, 0x60
	mov [esp], eax
	call handleScancode
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

	mov eax, 32
	mov dword [esp], timerHandler
	mov dword [esp+4], eax
	call setIDTEntry

	mov eax, 33
	mov dword [esp], keyboardHandler
	mov dword [esp+4], eax
	call setIDTEntry

	lidt [idtr]
	xchg bx, bx
	sti
	add esp, 12
	ret
