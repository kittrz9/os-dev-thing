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

selectionEnd: ; probably needs a better name
	dd 0

; will be used for commands too
lineBuffer:
	resb MAX_LINE_LENGTH+1
lineBufferIndex:
	dd 0

clearAllLines:
	push ebx
	push ecx

	mov ebx, dword [linesPtr]
	mov ecx, MAX_LINES*(MAX_LINE_LENGTH+1)
clearAllLinesLoop:
	mov byte [ebx], 0
	inc ebx
	loop clearAllLinesLoop

	pop ecx
	pop ebx
	ret


clearLine:
	push eax
	push ebx
	push ecx

	mov ebx, dword [linesPtr]
	mov eax, MAX_LINE_LENGTH+1
	mov ecx, dword [currentLine]
	mul ecx
	add ebx, eax
	mov ecx, MAX_LINE_LENGTH+1

clearLineLoop:
	mov byte [ebx], 0
	loop clearLineLoop

	pop ecx
	pop ebx
	pop eax
	ret

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
	mov eax, 0
	mov ecx, 10
parseDecimalLoop:
	movzx ebx, byte [esi]
	cmp bl, '0'
	jl parseDecimalEnd
	cmp bl, '9'
	jg parseDecimalEnd

	mul ecx

	sub ebx, '0'
	add eax, ebx
	inc esi
	jmp parseDecimalLoop
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



printMode:
	mov edi, dword [linesPtr]
	mov eax, dword [currentLine]
	mov ecx, MAX_LINE_LENGTH+1
	mul ecx
	add edi, eax

	mov ecx, dword [currentLine]
printModeLoop:
	cmp ecx, dword [selectionEnd]
	jg printModeEnd
	cmp ecx, dword [lastLine]
	jg printModeEnd

	push ecx
	mov eax, 0
	mov ebx, edi
	mov ecx, 0
	int 0x80
	pop ecx

	mov al, 0xa
	call printChar

	inc ecx
	add edi, MAX_LINE_LENGTH+1

	jmp printModeLoop
printModeEnd:

	ret



fileBufferPtr:
	dd 0
fileBufferSize:
	dd 0

writeMode:
	mov eax, 2 ; alloc
	mov ebx, MAX_LINES*(MAX_LINE_LENGTH+1)
	int 0x80
	mov dword [fileBufferPtr], ebx

	push esi
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
	pop esi

	mov ecx, edi
	sub ecx, dword [fileBufferPtr]

	mov eax, 5 ; write
	mov ebx, esi
	mov edx, ecx ; probably should change the syscall take the size from ecx
	mov ecx, dword [fileBufferPtr]
	int 0x80

	mov eax, 3 ; free
	mov ebx, dword [fileBufferPtr]
	mov ecx, MAX_LINES*(MAX_LINE_LENGTH+1)
	int 0x80
	ret


loadMode: ; should probably stop calling these modes
	call clearAllLines
	mov dword [lastLine], 0
	mov eax, 4 ; load file
	mov ebx, esi
	int 0x80
	cmp ebx, 0
	jne fileLoaded
	ret
fileLoaded:
	mov dword [fileBufferPtr], ebx
	mov dword [fileBufferSize], ecx

	mov edi, dword [linesPtr]
	mov edx, edi
	mov esi, ebx
	mov ebx, 0
loadModeLoop:
	mov al, byte [esi]
	inc esi
	cmp al, 0xa
	je loadNextLine
	mov byte [edi], al
	inc edi
	dec ecx
	jnz loadModeLoop
	jmp loadLineEnd

loadNextLine:
	add edx, MAX_LINE_LENGTH+1
	mov edi, edx
	inc ebx
	cmp ebx, MAX_LINES
	jl loadModeLoop
loadLineEnd:

	mov dword [lastLine], ebx


	mov eax, 3 ; free
	mov ebx, dword [fileBufferPtr]
	mov ecx, dword [fileBufferSize]
	int 0x80
	ret


; doesn't actually delete multiple lines yet lmao
deleteMode:
	mov eax, dword [lastLine]
	cmp eax, 0
	jne deleteModeNotLastLine
	call clearLine
	jmp deleteModeEnd
deleteModeNotLastLine:
	dec eax
	mov dword [lastLine], eax

	mov edi, dword [linesPtr]

	mov eax, MAX_LINE_LENGTH+1
	mov ebx, dword [currentLine]
	mul ebx
	add edi, eax

	mov esi, edi
	add esi, MAX_LINE_LENGTH+1

	mov edx, dword [selectionEnd]
	sub edx, dword [currentLine]

	mov eax, dword [lastLine]
	sub eax, dword [currentLine]
	inc eax
	mov ebx, MAX_LINE_LENGTH+1
	mul ebx
	mov ecx, eax
	rep movsb

deleteModeEnd:
	ret

global entry
entry:
	mov eax, 2 ; alloc
	mov ebx, MAX_LINES*(MAX_LINE_LENGTH+1)
	int 0x80
	mov dword [linesPtr], ebx

	call clearAllLines

mainLoop:
	call readLine
	mov al, 0xa
	call printChar

	mov esi, lineBuffer
	mov al, byte[esi]

	cmp al, '0'
	jl notNumber
	cmp al, '9'
	jg notNumber
	call parseDecimal
	mov dword [currentLine], eax
notNumber:

	mov eax, dword [currentLine]
	cmp eax, dword [lastLine]
	cmovg eax, dword [lastLine]
	mov dword [currentLine], eax
	mov dword [selectionEnd], eax
	mov al, byte[esi]
	cmp al, ','
	jne noSelectionEnd ; needs a better name

	inc esi
	call parseDecimal
	mov dword [selectionEnd], eax
noSelectionEnd:

	mov al, byte[esi]
	inc esi

	cmp al, 'q'
	je quit

	cmp al, 'i'
	jne notInsertMode
	call insertMode
notInsertMode:

	cmp al, 'p'
	jne notPrintMode
	call printMode
notPrintMode:

	cmp al, 'w'
	jne notWriteMode
	call writeMode
notWriteMode:

	cmp al, 'l'
	jne notLoadMode
	call loadMode
notLoadMode:

	cmp al, 'd'
	jne notDeleteMode
	call deleteMode
notDeleteMode:

	mov al, 0
	mov byte [lineBuffer], al
	jmp mainLoop
quit:
	mov eax, 3 ; free
	mov ebx, dword [linesPtr]
	mov ecx, MAX_LINES*(MAX_LINE_LENGTH+1)
	int 0x80
	ret
