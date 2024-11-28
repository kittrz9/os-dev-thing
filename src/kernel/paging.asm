bits 32

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

