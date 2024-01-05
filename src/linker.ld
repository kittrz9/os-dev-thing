OUTPUT_FORMAT("binary")

ENTRY(_start)

SECTIONS {
	. = 0x0;
	.bootstrap : {
		*(.bootstrap)
	}

	. = 0x1BE;
	.part1entry : {
		*(.part1entry)
	}

	. = 0x1CE;
	.part2entry : {
		*(.part2entry)
	}

	. = 0x1DE;
	.part3entry : {
		*(.part3entry)
	}

	. = 0x1EE;
	.part4entry : {
		*(.part4entry)
	}

	. = 0x1FE;
	.magic : {
		*(.magic)
	}
}
