bits 32

; I forgot that gcc shuffles around functions so stage2 wasn't at the start
; and it was calling outb and then returning
; this fixes that

section .entry
extern stage2
entry:
	jmp stage2
