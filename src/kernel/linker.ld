OUTPUT_FORMAT("elf32-i386")

ENTRY(kernel)

SECTIONS {
	/* https://wiki.osdev.org/Higher_Half_x86_Bare_Bones#linker.ld */
	. = 0x100000;
	.entry : {
		*(.entry);
	}
	. += 0x80000000;
	.text ALIGN(4K) : AT(ADDR(.text) - 0x80000000) {
		*(.text);
	}

	.rodata ALIGN(4K) : AT(ADDR(.rodata) - 0x80000000) {
		*(.rodata);
	}

	.data ALIGN(4K) : AT(ADDR(.data) - 0x80000000) {
		*(.data);
	}
	.bss ALIGN(4K) : AT(ADDR(.bss) - 0x80000000) {
		*(.bss);
	}
	endPage = ALIGN(4K);
	/DISCARD/ : {
		*(.debug_info)
		*(.debug_abbrev)
		*(.debug_loclists)
		*(.debug_aranges)
		*(.debug_line)
		*(.debug_str)
		*(.debug_line_str)
		*(.comment)
		*(.debug_frame)
		*(.debug_rnglists)
	}
}

