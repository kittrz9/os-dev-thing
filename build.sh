#!/bin/sh

set -xe

ORIGIN_DIR="$(readlink -f "$(dirname "$0")")"
export ORIGIN_DIR

# I don't think you can use the source command in posix sh
# so I gotta use this instead
# https://stackoverflow.com/questions/11588583/is-the-shells-source-posix-standard
. ./get-tools.sh

cd "$ORIGIN_DIR"

if [ -z "$(command -v "$LD")" ]; then
	echo "cross compiler not found"
	exit 1
fi

CFLAGS="$CFLAGS -g -Wall -Wextra -Wpedantic -std=gnu99 -ffreestanding -fPIE -m64 -march=x86-64"
LDFLAGS="$LDFLAGS -nostdlib -static --no-dynamic-linker -z text -z max-page-size=0x1000 -T src/linker.ld -Map=build/os.map"
INCLUDES="$INCLUDES "
DEFINES="$DEFINES "

rm -rf build/ obj/
mkdir -p build/ obj/

OBJS=""

CFILES=$(find src/ -name "*.c")
ASMFILES=$(find src/ -name "*.s")

# had to stop using the linker since nasm refuses to let me change the origin, so all addresses are off by 0x7c00 lmao
nasm -g -fbin src/boot.s -o build/boot.bin

#if [ "$ASMFILES" ]; then
#	for f in $ASMFILES; do
#		OBJNAME=$(echo "$f" | sed -e "s/\.s/\.o/" -e "s/src/obj/")
#		nasm -felf64 "$f" -o "$OBJNAME"
#		OBJS="$OBJNAME $OBJS"
#	done
#fi
#
#if [ "$CFILES" ]; then
#	for f in src/*.c; do
#		OBJNAME=$(echo "$f" | sed -e "s/\.c/\.o/" -e "s/src/obj/")
#		$CC $CFLAGS $DEFINES $INCLUDES -o "$OBJNAME" -c "$f"
#		OBJS="$OBJNAME $OBJS"
#	done
#fi
#
#$LD $OBJS $LDFLAGS -o build/os.bin

