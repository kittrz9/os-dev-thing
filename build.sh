#!/bin/sh


# THIS NEEDS TO BE CHANGED ANY TIME THE CROSS COMPILER IS MOVED OR (RE)BUILT
export PATH="/mnt/disk1/cross-compiler/build-cross-x86_64/gcc-13.2.0/bin:$PATH"

CC=x86_64-elf-gcc
LD=x86_64-elf-ld

if [ -z "$(command -v $LD)" ]; then
	echo "cross compiler not found"
	exit 1
fi

set -xe

CFLAGS="$CFLAGS -g -Wall -Wextra -Wpedantic -std=gnu99 -ffreestanding -fPIE -m64 -march=x86-64"
LDFLAGS="$LDFLAGS -nostdlib -static -pie --no-dynamic-linker -z text -z max-page-size=0x1000 -T src/linker.ld -Map=build/os.map"
INCLUDES="$INCLUDES "
DEFINES="$DEFINES "

rm -rf build/ obj/
mkdir -p build/ obj/

OBJS=""

CFILES=$(find src/ -name "*.c")
ASMFILES=$(find src/ -name "*.s")

if [ "$ASMFILES" ]; then
	for f in $ASMFILES; do
		OBJNAME=$(echo "$f" | sed -e "s/\.s/\.o/" -e "s/src/obj/")
		nasm -felf64 "$f" -o "$OBJNAME"
		OBJS="$OBJNAME $OBJS"
	done
fi

if [ "$CFILES" ]; then
	for f in src/*.c; do
		OBJNAME=$(echo "$f" | sed -e "s/\.c/\.o/" -e "s/src/obj/")
		$CC $CFLAGS $DEFINES $INCLUDES -o "$OBJNAME" -c "$f"
		OBJS="$OBJNAME $OBJS"
	done
fi

$LD $OBJS $LDFLAGS -o build/os.bin

