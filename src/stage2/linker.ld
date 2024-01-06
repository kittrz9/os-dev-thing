OUTPUT_FORMAT("elf64-x86-64")

ENTRY(stage2)

SECTIONS {
	. = 0x10000;
	.text : {
		*(.text)
	}
}
