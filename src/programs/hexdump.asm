bits 32

%define FILENAME_MAX_LENGTH 32

fileName:
	resb FILENAME_MAX_LENGTH+1
fileSize:
	resd 1
fileBuffer:
	resd 1
byteChars:
	resb 2
hexCharsLUT:
	db "0123456789ABCDEF"
global entry
entry:
	mov ecx, 0
	mov edi, fileName
readKey:
	; read key syscall
	mov eax, 1
	int 0x80
	cmp ebx, 0
	je readKey
	cmp ebx, 0xa
	je endInput
	mov byte [edi], bl
	push ecx
	mov eax, 0
	mov ecx, 1
	mov ebx, edi
	int 0x80
	pop ecx
	inc edi
	inc ecx
	cmp ecx, FILENAME_MAX_LENGTH
	jl readKey
endInput:
	mov byte [edi], 0
	dec esp
	mov byte [esp], 0xa
	mov eax, 0
	mov ebx, esp
	mov ecx, 1
	int 0x80
	inc esp

	mov eax, 4
	mov ebx, fileName
	int 0x80
	mov dword [fileSize], ecx
	mov dword [fileBuffer], ebx

hexdumpLoop:
	mov al, byte [ebx]
	mov edi, byteChars+1
	mov esi, eax
	and esi, 0xF
	add esi, hexCharsLUT
	mov dl, byte [esi]
	mov byte [edi], dl
	dec edi
	mov esi, eax
	shr esi, 4
	and esi, 0xF
	add esi, hexCharsLUT
	mov al, byte [esi]
	mov byte [edi], al
	push ebx
	push ecx
	mov eax, 0
	mov ebx, edi
	mov ecx, 2
	int 0x80
	pop ecx
	pop ebx
	inc ebx
	dec ecx
	jnz hexdumpLoop

	; free
	mov eax, 3
	mov ebx, dword [fileSize]
	int 0x80

	mov byte [edi], 0
	dec esp
	mov byte [esp], 0xa
	mov eax, 0
	mov ebx, esp
	mov ecx, 1
	int 0x80
	inc esp

	ret
