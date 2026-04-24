bits 32


instrMovName:
	db "mov",0

instrRetName:
	db "ret",0
instrRetBytes:
	db 0xc3
instrRetByteCount: equ $-instrRetBytes

; name, argCount, bytes, byteCount
instructions:
	dd instrRetName, 0, instrRetBytes, instrRetByteCount
	dd 0 ; end


programBufferPtr:
	dd 0
programBufferSize:
	dd 0

addBytes:
	mov edi, dword [programBufferPtr]
	mov eax, dword [programBufferSize]
	add edi, eax
	add eax, ecx
	mov dword [programBufferSize], eax
	rep movsb
	ret


instrNameBuffer:
	resb 32

; still needs to find the arg count
findInstrByName:
	mov edi, instrNameBuffer
instrNameLoop:
	mov al, byte [esi]
	inc esi
	cmp al, 0xa
	je instrNameLoopEnd
	cmp al, ' '
	jle instrNameLoop
	mov byte [edi], al
	inc edi
	jmp instrNameLoop
instrNameLoopEnd:
	mov byte [edi], 0
;	mov eax, 0
;	mov ebx, instrNameBuffer
;	mov ecx, 0
;	int 0x80

	mov edx, instructions
instrSearchLoop:
	mov esi, instrNameBuffer
	mov edi, dword [edx]
	cmp edi, 0
	je instrNotFound
	rep cmpsb
	je instrFound
	add edx, 4*4
	jmp instrSearchLoop
instrFound:

	mov eax, 0 ; print
	mov ebx, dword [edx]
	mov ecx, 0
	int 0x80


instrNotFound:
	ret



fileBufferPtr:
	dd 0
fileBufferSize:
	dd 0

testFileName:
	db "test.asm",0
global entry
entry:
	mov eax, 4 ; read file
	mov ebx, testFileName
	int 0x80
	cmp ebx, 0
	jne fileFound
	ret
fileFound:
	mov dword [fileBufferPtr], ebx
	mov dword [fileBufferSize], ecx

	mov esi, ebx
	call findInstrByName

	mov eax, 3 ; free
	mov ebx, dword [fileBufferPtr]
	mov ecx, dword [fileBufferSize]
	int 0x80
	ret
