#!/bin/sh

cd "$ORIGIN_DIR"

mkdir "$ORIGIN_DIR"/build/programs

PROGRAMS="$(find src/programs/ -name "*.asm")"
for f in $PROGRAMS; do
	PROGRAM_OUT="$ORIGIN_DIR"/build/programs/"$(basename "$f" | sed -e "s/\.asm/\.elf/")"
	PROGRAM_OBJ="$(echo $PROGRAM_OUT | sed -e "s/\.elf/\.o/")"

	nasm -felf32 "$f" -o "$PROGRAM_OBJ"

	$LD $PROGRAM_OBJ $LDFLAGS -T src/programs/linker.ld -o $PROGRAM_OUT
done
