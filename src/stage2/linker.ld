OUTPUT_FORMAT("elf32-i386")

ENTRY(stage2)

SECTIONS {
	. = 0xc0000;
	.text : {
		*(.entry);
		*(.text);
	}

	.rodata : {
		*(.rodata);
	}

	.data : {
		*(.data);
	}
	.bss : {
		*(.bss);
	}
	stage2End = .;
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

