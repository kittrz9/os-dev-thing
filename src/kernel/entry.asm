bits 32

; https://wiki.osdev.org/Paging
; https://stackoverflow.com/questions/18431261/how-does-x86-paging-work/18431262#18431262
; https://wiki.osdev.org/Higher_Half_x86_Bare_Bones

%define virtToPhys(a) (a - 0x80000000)
; bits 32 to 22 are page dir
; bits 22 to 12 are page table
; bits 12 to 0 are offset
%define dirFromAddr(a) (a >> 22)
%define tableFromAddr(a) ((a >> 12)&0xFFF)

global vbeInfo

section .bss
align 0x1000
pageDir:
	resb 0x1000
pageTable:
	resb 0x1000
vbeInfo:
	resb 0x100
stackBottom:
	resb 0x4000 ; 16k
stackTop:

section .entry
extern kernel
entry:
	; copy vbe info
	; doing this here since it'd probably make it easier when I start working on paging
	mov esi, dword [esp-0x8] ; old vbe ptr
	mov edi, virtToPhys(vbeInfo)
	mov ecx, 0x100
	rep movsb

	; set up paging stuff
	; identity map 0x100000
	mov edi, virtToPhys(pageDir)
	mov esi, virtToPhys(pageTable)
	mov eax, esi
	or eax, 3 ; present and r/w bit
	mov dword[edi], eax
	; and map that to 0x80000000
	add edi, dirFromAddr(0x80000000)*4
	mov dword[edi], eax

	mov ecx, 0xf00
	mov edi, 0x100000
	add esi, tableFromAddr(0x100000)*4
fillPageTable:
	mov eax, edi
	or eax, 3 ; present and r/w bit
	mov dword[esi], eax
	add edi, 0x1000
	add esi, 4
	loop fillPageTable

	; enable paging
	mov eax, virtToPhys(pageDir)
	mov cr3, eax

	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax

	; jump to virtual address
	mov eax, testJmp
	jmp eax

section .text
testJmp:
	mov esp, stackTop
	
	jmp kernel
