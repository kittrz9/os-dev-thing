bits 32

asdf:
	db "printing from test.elf!!!", 0xa
global entry
entry:
	lea eax, asdf
	int 0x80
	; jmp entry
	ret
