bits 32

asdf:
	db "printing from test.elf!!!", 0xa, 0
global entry
entry:
	pushad
	mov eax, 0
	lea ebx, asdf
	int 0x80
	; jmp entry
	popad
	ret
