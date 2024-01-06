#!/bin/sh

cd "$ORIGIN_DIR"

CFILES="$(find src/stage2/ -name "*.c")"
for f in $CFILES; do
	OBJNAME="$(echo "$f" | sed -e "s/\.c/\.o/" -e "s/src/obj/")"
	echo "obj $OBJNAME"
	OBJDIR="$(dirname $OBJNAME)"
	echo "dir $OBJDIR"
	if [ ! -d "$OBJDIR" ]; then
		mkdir -p "$OBJDIR"
	fi

	$CC $CFLAGS $DEFINES $INCLUDES -o "$OBJNAME" -c "$f"

	OBJS="$OBJNAME $OBJS"
done

echo $OBJS

#if [ "$CFILES" ]; then
#	for f in src/*.c; do
#		OBJNAME=$(echo "$f" | sed -e "s/\.c/\.o/" -e "s/src/obj/")
#		$CC $CFLAGS $DEFINES $INCLUDES -o "$OBJNAME" -c "$f"
#		OBJS="$OBJNAME $OBJS"
#	done
#fi

$LD $OBJS $LDFLAGS -T src/stage2/linker.ld -o build/stage2.elf
$OBJCOPY -O binary build/stage2.elf build/stage2.bin

# will need to change this once it gets above 1 sector in size
truncate build/stage2.bin -s 512
