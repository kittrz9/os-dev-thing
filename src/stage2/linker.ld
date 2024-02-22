OUTPUT_FORMAT("elf32-i386")

ENTRY(stage2)

SECTIONS {
	. = 0xc0000;
	.text : {
		*(.entry)
		*(.text)
	}

	.rodata : {
		*(.rodata)
	}

	.data : {
		*(.data)
	}
	.bss : {
		*(.bss)
	}
}

