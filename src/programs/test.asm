bits 32

asdf:
	db "printing from test.elf!!!", 0xa, 0
file:
	db "TODO.md", 0
global entry
entry:
	pushad
	mov eax, 0
	lea ebx, asdf
	mov ecx, 0
	int 0x80

	sub esp, 4
	mov ecx, 1
keyCheck:
	mov eax, 1
	int 0x80
	cmp ebx, 0
	je keyCheck
	cmp ebx, 0xa
	je end
	mov eax, 0
	mov [esp], ebx
	mov ebx, esp
	int 0x80
	jmp keyCheck
end:
	;mov eax, 0
	;mov dword [esp], 0xa
	;mov ebx, esp
	;int 0x80
	mov eax, 4
	lea ebx, file
	int 0x80
	mov eax, 0
	int 0x80
	mov eax, 3
	mov ebx, ecx
	add esp, 4


	; jmp entry
	popad
	ret
