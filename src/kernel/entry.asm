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
fbPageTable:
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
	; map 0xF0000000 to the framebuffer page table
	mov edi, virtToPhys(pageDir)+dirFromAddr(0xF0000000)*4
	mov eax, virtToPhys(fbPageTable)
	or eax, 3 ; present and r/w bit
	mov dword[edi], eax

	mov ecx, 0x1000
	mov edi, 0x100000
	add esi, tableFromAddr(0x100000)*4
fillPageTable:
	mov eax, edi
	or eax, 3 ; present and r/w bit
	mov dword[esi], eax
	add edi, 0x1000
	add esi, 4
	loop fillPageTable


	; I've mapped *something* to this memory region
	; since I can write to it and read that back to confirm
	; writing to it doesn't actually write to the framebuffer though
	; most values in the tables seem to be correct after checking with gdb
	; probably dumb segment shenanigans
	; still commiting this since it's at least progress
	mov ecx, 0x1000
	mov edi, dword[virtToPhys(vbeInfo)+40] ; fb address is at this offset
	mov ebx, edi
	and edi, 0xFFFFF000 ; remove offset from the fb address
	mov esi, virtToPhys(fbPageTable)
fillFBPageTable:
	mov eax, edi
	or eax, 3 ; present and r/w bit
	mov dword[esi], eax
	add edi, 0x1000
	add esi, 4
	loop fillFBPageTable

	and ebx, 0xFFF ; get rid of page dir bits
	or ebx, 0xF0000000 ; and change it to this
	mov dword[virtToPhys(vbeInfo)+40], ebx

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
	; set up gdt again
	lgdt [gdtr]

	mov esp, stackTop

	jmp kernel


; gdt copied from boot.asm
section .data
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
