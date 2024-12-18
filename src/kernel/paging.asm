bits 32

; bits 32 to 22 are page dir
; bits 22 to 12 are page table
; bits 12 to 0 are offset

%macro virtToPhys 1
	sub %1, 0x80000000
%endmacro

%macro physToVirt 1
	add %1, 0x80000000
%endmacro

%macro dirFromAddr 1
	shr %1, 22
%endmacro

%macro tableFromAddr 1
	shr %1, 12
	and %1, 0xBFF
%endmacro

global pageDir
global firstPageTable
global fbPageTable

section .bss
align 0x1000
pageDir:
	resb 0x1000
firstPageTable:
	resb 0x1000
fbPageTable:
	resb 0x1000

section .text

extern serialWriteHex32
extern pageAlloc

; void mapPage(void* physAddr, void* virtAddr);
global mapPage
mapPage:
	push ebp
	mov ebp, esp
	pushad
	mov esi, [ebp+8] ; physAddr
	mov edi, [ebp+12] ; virtAddr
	mov eax, edi
	dirFromAddr eax
	mov edx, 4
	mul edx
	add eax, pageDir
	mov ebx, [eax]
	; check here if the present bit is set, and if not grab a page with pageAlloc and use that
	and ebx, 1
	jnz pageTableAlreadyAllocated
	push eax
	sub esp, 4
	mov dword [esp], 0x1000
	call pageAlloc
	add esp, 4
	pop ecx
	mov ebx, eax
	virtToPhys eax
	or eax, 3 ; present and rw bits
	mov [ecx], eax
	mov eax, [ecx]
	mov eax, ebx
	jmp pageTableAllocatedCheckEnd
pageTableAlreadyAllocated:
	mov eax, [eax]
	and eax, 0xFFFFF000
	physToVirt eax
pageTableAllocatedCheckEnd:
	; eax has page table address
	mov ebx, eax
	mov eax, edi
	tableFromAddr eax
	mov edx, 4
	mul edx
	add eax, ebx
	; dont think I actually need to check the present bit if I'm just going to overwrite the page table entry anyway
	mov ebx, esi
	and ebx, 0xFFFFF000
	or ebx, 3 ; present and rw bits
	mov [eax], ebx

	mov eax, cr3
	mov cr3, eax

	popad
	pop ebp
	ret

; void mapPages(void* physAddr, void* virtAddr, uint16_t pageCount);
global mapPages
mapPages:
	push ebp
	mov ebp, esp
	pushad

	mov esi, [ebp+8] ; physAddr
	mov edi, [ebp+12] ; virtAddr
	mov cx, [ebp+16] ; pageCount

	sub esp, 12
pageLoop:
	mov [esp], esi
	mov [esp+4], edi
	call mapPage
	add esi, 0x1000
	add edi, 0x1000
	dec cx
	jnz pageLoop
	add esp, 12


	popad
	pop ebp
	ret


