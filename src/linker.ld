OUTPUT_FORMAT("binary")

ENTRY(_start)

SECTIONS {
	. = 0x0;
	.bootstrap : {
		*(.bootstrap)
	}

	. = 0x1FE;
	.magic : {
		*(.magic)
	}
}
