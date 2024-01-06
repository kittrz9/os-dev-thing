#!/bin/sh

if [ -z "$ORIGIN_DIR" ]; then
	ORIGIN_DIR="$(readlink -f $(dirname $0))"
fi

TOOLS_DIR="$ORIGIN_DIR/tools/"

cd "$TOOLS_DIR" || exit 1

THREAD_COUNT="$(nproc)"

if [ ! -d "$TOOLS_DIR" ]; then
	mkdir "$TOOLS_DIR"
fi

# build nasm if not found
if [ -z "$(command -v nasm)" ] && [ ! -d "./nasm" ]; then
	git clone https://github.com/netwide-assembler/nasm --depth=1 --branch nasm-2.16.02rc7 nasm
	cd nasm || exit 1
	./autogen.sh
	./configure
	make "-j$THREAD_COUNT"
	export PATH="$PATH:./tools/nasm/"
fi

# build cross compiler
# assuming the compiler is new enough to not need to bootstrap
PREFIX="$ORIGIN_DIR/tools/cross-compiler"
mkdir -p "$PREFIX"
TARGET="x86_64-none-elf"
BINUTILS_DIR="binutils-cross"
GCC_DIR="gcc-cross"

cd "$TOOLS_DIR" || exit 1

if [ ! -d "./$BINUTILS_DIR" ]; then
	mkdir -p "$BINUTILS_DIR"
fi
cd "$BINUTILS_DIR" || exit 1

if [ ! -f "binutils-2.41.tar.xz" ]; then
	wget https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.xz
fi

if [ ! -d "binutils-2.41" ]; then
	tar -xavf binutils-2.41.tar.xz
fi

if [ ! -f "$PREFIX/bin/$TARGET-ld" ]; then
	./binutils-2.41/configure "--target=$TARGET" "--prefix=$PREFIX" --with-sysroot --disable-nls --disable-werror
	make "-j$THREAD_COUNT"
	make install
fi

cd "$TOOLS_DIR" || exit 1
if [ ! -d "./$GCC_DIR" ]; then
	mkdir -p "$GCC_DIR"
fi
cd "$GCC_DIR" || exit 1

if [ ! -f "gcc-13.2.0.tar.xz" ]; then
	wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.xz
fi

if [ ! -d "gcc-13.2.0" ]; then
	tar -xavf gcc-13.2.0.tar.xz
fi

if [ ! -f "$PREFIX/bin/$TARGET-gcc" ]; then
	./gcc-13.2.0/configure "--target=$TARGET" "--prefix=$PREFIX" --disable-nls --enable-languages=c --without-headers
	make all-gcc "-j$THREAD_COUNT"
	make all-target-libgcc "-j$THREAD_COUNT"
	make install-gcc
	make install-target-libgcc
fi

export PATH="$PATH:$PREFIX/bin/"
export CC="$TARGET-gcc"
export LD="$TARGET-ld"
export OBJCOPY="$TARGET-objcopy"

if [ -z "$(command -v $CC)" ]; then
	echo "cross compiler not found"
	exit 1
fi

cd "$ORIGIN_DIR" || exit

