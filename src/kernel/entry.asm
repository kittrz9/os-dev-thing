bits 32

global vbeInfo

section .bss
vbeInfo:
	resb 0x100
; should probably align this to a 4k page or whatever, but nasm throws a ton of warnings if I try
stackBottom:
	resb 0x4000 ; 16k
stackTop:

section .entry
extern kernel
entry:
	; copy vbe info
	; doing this here since it'd probably make it easier when I start working on paging
	mov esi, dword [esp-0x8] ; old vbe ptr
	mov edi, vbeInfo
	mov ecx, 0x100
	rep movsb

	mov esp, stackTop
	
	jmp kernel
