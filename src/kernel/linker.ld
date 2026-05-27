OUTPUT_FORMAT("elf32-i386")

ENTRY(kernel)

SECTIONS {
	/* https://wiki.osdev.org/Higher_Half_x86_Bare_Bones#linker.ld */
	. = 0x100000;
	.entry : {
		*(.entry);
	}
	. += 0x80000000;
	/* having it set to align at 4k would probably be good for setting up page protections
	but for now it doesn't really matter and just makes the file size of the kernel huge
	which also doesn't matter in the slightest but I wanted to see how big the kernel was without it */
	.text ALIGN(4) : AT(ADDR(.text) - 0x80000000) {
		*(.text);
	}

	.rodata ALIGN(4) : AT(ADDR(.rodata) - 0x80000000) {
		*(.rodata);
	}

	.data ALIGN(4) : AT(ADDR(.data) - 0x80000000) {
		*(.data);
	}
	bssStart = ALIGN(4K);
	.bss ALIGN(4K) : AT(ADDR(.bss) - 0x80000000) {
		*(.bss);
	}
	bssEnd = ALIGN(4);
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

