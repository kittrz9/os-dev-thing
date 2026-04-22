bits 32

%define MAX_LINES 1024
%define MAX_LINE_LENGTH 64

;lines:
;	resb MAX_LINES*(MAX_LINE_LENGTH+1)
linesPtr:
	dd 0
currentLine:
	dd 0
lastLine:
	dd 0

; will be used for commands too
lineBuffer:
	resb MAX_LINE_LENGTH+1
lineBufferIndex:
	dd 0

printChar:
	push ebx
	push ecx

	sub esp, 1
	mov byte [esp], al
	mov eax, 0 ; print
	mov ebx, esp
	mov ecx, 1
	int 0x80
	add esp, 1

	pop ecx
	pop ebx
	ret



parseDecimal:
	mov edi, esi
findDecimalEnd:
	mov al, byte [edi]
	cmp al, '0'
	jl decimalEndFound
	cmp al, '9'
	jg decimalEndFound
	inc edi
	jmp findDecimalEnd
decimalEndFound: ; needs a better name

	mov eax, 0
	mov ecx, 10
parseDecimalLoop:
	dec edi
	mul ecx

	movzx ebx, byte [edi]
	sub ebx, '0'
	add eax, ebx

	cmp edi, esi
	jne parseDecimalLoop
parseDecimalEnd:
	ret


readLine:
	push edi
	mov dword [lineBufferIndex], 0
	mov ecx, dword [lineBufferIndex]
	mov edi, lineBuffer
	add edi, ecx
readChar:
	mov eax, 1 ; read
	int 0x80
	cmp ebx, 0
	je readChar
	cmp ebx, 0xa
	je endInput

	cmp bl, 0x8 ; backspace
	jne notBackspace
	cmp ecx, 0
	je readChar
	mov al, bl
	call printChar
	dec ecx
	mov byte [edi], 0
	dec edi
	mov dword [lineBufferIndex], ecx
	jmp readChar
notBackspace:
	cmp ecx, MAX_LINE_LENGTH
	jge readChar

	mov al, bl
	call printChar

	mov byte [edi], bl
	inc ecx
	inc edi
	mov dword [lineBufferIndex], ecx

	jmp readChar
endInput:
	mov byte [edi], 0
	pop edi
	ret



insertMode:
	mov edi, dword [linesPtr]
	mov eax, dword [currentLine]
	mov ecx, MAX_LINE_LENGTH+1
	mul ecx
	add edi, eax
insertModeLoop:
	mov ecx, dword [currentLine]
	cmp ecx, MAX_LINES
	jge insertModeEnd

	call readLine
	mov al, 0xa
	call printChar

	mov al, byte [lineBuffer]
	cmp al, '.'
	je insertModeEnd

	mov esi, lineBuffer
	push edi
	rep movsb
	mov byte [edi], 0
	pop edi

	mov ecx, dword [currentLine]
	cmp ecx, dword [lastLine]
	jle notLastLine
	mov dword [lastLine], ecx
notLastLine:
	inc ecx
	mov dword [currentLine], ecx

	add edi, MAX_LINE_LENGTH+1

	jmp insertModeLoop
insertModeEnd:
	ret



listMode:
	mov edi, dword [linesPtr]
	mov eax, dword [currentLine]
	mov ecx, MAX_LINE_LENGTH+1
	mul ecx
	add edi, eax
	mov eax, 0
	mov ebx, edi
	mov ecx, 0
	int 0x80

	mov al, 0xa
	call printChar

	ret



fileBufferPtr:
	dd 0

writeMode:
	mov eax, 2 ; alloc
	mov ebx, MAX_LINES*(MAX_LINE_LENGTH+1)
	int 0x80
	mov dword [fileBufferPtr], ebx

	mov edi, ebx
	mov edx, dword [linesPtr]
	mov ecx, 0
nextLine:
	cmp ecx, dword [lastLine]
	jg fileEnd
	mov esi, edx

nextChar:
	mov al, byte [esi]
	cmp al, 0
	jne notNextLine
	add edx, MAX_LINE_LENGTH+1
	mov byte [edi], 0xa
	inc edi
	inc ecx
	jmp nextLine
notNextLine:
	mov byte [edi], al

	inc edi
	inc esi
	jmp nextChar
fileEnd:

	mov ecx, edi
	sub ecx, dword [fileBufferPtr]

	mov eax, 5 ; write
	mov ebx, lineBuffer+1
	mov edx, ecx ; probably should change the syscall take the size from ecx
	mov ecx, dword [fileBufferPtr]
	int 0x80

	mov eax, 3 ; free
	mov ebx, dword [fileBufferPtr]
	mov ecx, MAX_LINES*(MAX_LINE_LENGTH+1)
	int 0x80
	ret



global entry
entry:
	mov eax, 2 ; alloc
	mov ebx, MAX_LINES*(MAX_LINE_LENGTH+1)
	int 0x80
	mov dword [linesPtr], ebx

	mov ecx, MAX_LINES*(MAX_LINE_LENGTH+1)
bufferInit:
	mov byte [ebx], 0
	inc ebx
	loop bufferInit

mainLoop:
	call readLine
	mov al, 0xa
	call printChar

	mov al, byte[lineBuffer]
	cmp al, 'q'
	je quit

	cmp al, 'i'
	jne notInsertMode
	call insertMode
notInsertMode:

	cmp al, 'l'
	jne notListMode
	call listMode
notListMode:

	cmp al, 'w'
	jne notWriteMode
	call writeMode
notWriteMode:

	cmp al, '0'
	jl notNumber
	cmp al, '9'
	jg notNumber
	mov esi, lineBuffer
	call parseDecimal
	mov dword [currentLine], eax
notNumber:

	mov al, 0
	mov byte [lineBuffer], al
	jmp mainLoop
quit:
	mov eax, 3 ; free
	mov ebx, dword [linesPtr]
	mov ecx, MAX_LINES*(MAX_LINE_LENGTH+1)
	int 0x80
	ret
