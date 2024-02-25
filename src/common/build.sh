#!/bin/sh

cd "$ORIGIN_DIR"

CFILES="$(find src/common/ -name "*.c")"
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

ASMFILES="$(find src/common/ -name "*.asm")"
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

#echo $OBJS

