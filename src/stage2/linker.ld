OUTPUT_FORMAT("elf32-i386")

ENTRY(stage2)

SECTIONS {
	. = 0x7e00;
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

