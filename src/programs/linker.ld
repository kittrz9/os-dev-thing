OUTPUT_FORMAT("elf32-i386")

PHDRS {
	headers PT_PHDR PHDRS;
	everything PT_LOAD FILEHDR PHDRS FLAGS(7);
}

ENTRY(entry)

SECTIONS {
	. = SIZEOF_HEADERS + 0x40000;
	.text : {
		*(.text);
		*(.rodata);
		*(.data);
		*(.bss);
	} :everything
	/DISCARD/ : {
		*(.symtab)
		*(.strtab)
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

