
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
extern serialWriteHex32
section .text
align 4
interruptHandler:
	pushad
	sub esp, 4
	lea eax, interruptStr
	mov [esp], eax
	call serialWriteStr
	add esp, 4
	; acknowledge to PIC
	mov al, 0x20
	out 0x20, al
	in al, 0x60 ; discard scancode
	popad
	iret

section .rodata
pageFaultStr:
	db "page fault!!!!!", 0xa, 0x0

section .text
align 4
pageFaultHandler:
	sub esp, 4
	lea eax, pageFaultStr
	mov [esp], eax
	call serialWriteStr
	add esp, 4
	pop eax
	call serialWriteHex32
	cli
	hlt

section .data
termUpdateCounter:
	dq 20
; https://wiki.osdev.org/Programmable_Interval_Timer#Using_the_IRQ_to_Implement_sleep
extern countDown
extern drawTerm
align 4
timerHandler:
	pushad
	mov eax, [countDown]
	test eax, eax
	jz timerDone
	dec eax
	mov [countDown], eax
timerDone:
	; this should really be done with multitasking but whatever this works for now
	mov eax, [termUpdateCounter]
	dec eax
	jnz noTermUpdate
	call drawTerm
	mov eax, 20
noTermUpdate:
	mov [termUpdateCounter], eax
	mov al, 0x20
	out 0x20, al
	popad
	iret

extern handleScancode
section .text
align 4
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

extern handleSyscalls
align 4
softwareIntHandler:
	push ebp
	mov ebp, esp
	sub esp, 4*6
	mov [esp], eax
	mov [esp+4], ebx
	mov [esp+8], ecx
	mov [esp+12], edx
	mov [esp+16], edi
	mov [esp+20], esi
	push esp
	call handleSyscalls
	pop esp
	add esp, 4*6
	mov ebx, [eax+4]
	mov ecx, [eax+8]
	mov edx, [eax+12]
	mov edi, [eax+16]
	mov esi, [eax+20]
	mov eax, [eax]
	push eax
	mov al, 0x20
	out 0x20, al
	pop eax
	mov esp, ebp
	pop ebp
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

	mov eax, 14
	mov dword [esp], pageFaultHandler
	mov dword [esp+4], eax
	call setIDTEntry

	mov eax, 0x80
	mov dword [esp], softwareIntHandler
	mov dword [esp+4], eax
	call setIDTEntry

	lidt [idtr]
	xchg bx, bx
	sti
	add esp, 12

	ret
