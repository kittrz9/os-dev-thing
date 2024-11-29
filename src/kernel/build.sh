#!/bin/sh

cd "$ORIGIN_DIR"

OBJS="$(find obj/common/ -type f)"

CFILES="$(find src/kernel/ -name "*.c")"
for f in $CFILES; do
	OBJNAME="$(echo "$f" | sed -e "s/\.c/\.o/" -e "s/src/obj/")"
	echo "obj $OBJNAME"
	OBJDIR="$(dirname $OBJNAME)"
	echo "dir $OBJDIR"
	if [ ! -d "$OBJDIR" ]; then
		mkdir -p "$OBJDIR"
	fi

	$CC $CFLAGS $DEFINES -D KERNEL $INCLUDES -o "$OBJNAME" -c "$f"

	OBJS="$OBJNAME $OBJS"
done

ASMFILES="$(find src/kernel/ -name "*.asm")"
for f in $ASMFILES; do
	OBJNAME="$(echo "$f" | sed -e "s/\.asm/\.o/" -e "s/src/obj/")"
	echo "obj $OBJNAME"
	OBJDIR="$(dirname $OBJNAME)"
	echo "dir $OBJDIR"
	if [ ! -d "$OBJDIR" ]; then
		mkdir -p "$OBJDIR"
	fi

	#$CC $CFLAGS $DEFINES $INCLUDES -o "$OBJNAME" -c "$f"
	nasm -felf32 "$f" -o "$OBJNAME"

	OBJS="$OBJNAME $OBJS"
done

echo $OBJS

$LD $OBJS $LDFLAGS -T src/kernel/linker.ld -o build/kernel.elf -Map=build/kernel.map
$OBJCOPY -O binary build/kernel.elf build/kernel.bin

