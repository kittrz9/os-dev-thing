bits 32

; I forgot that gcc shuffles around functions so stage2 wasn't at the start
; and it was calling outb and then returning
; this fixes that

extern bssStart
extern bssEnd
section .entry
extern stage2
entry:
	; I can't get it to replicate whatever issue I was having with uninitialized bss
	; but this hopefully fixes it entirely
	; I also probably should've been doing this from the start lmao
	mov edi, bssStart
	mov ecx, bssEnd
	sub ecx, bssStart ; just doing bssEnd-bssStart doesn't work, probably could get the linker to define the size of the bss section but who cares
	xor eax, eax
bssInitLoop:
	mov dword[edi], eax
	add edi, 4
	loop bssInitLoop
	jmp stage2
