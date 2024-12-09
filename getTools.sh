#!/bin/sh

. ./config.sh

if [ -z "$ORIGIN_DIR" ]; then
	ORIGIN_DIR="$(readlink -f $(dirname $0))"
fi

TOOLS_DIR="$ORIGIN_DIR/tools/"

cd "$ORIGIN_DIR" || exit 1

if [ ! -d "$TOOLS_DIR" ]; then
	mkdir "$TOOLS_DIR"
fi

# build nasm if not found
if [ -z "$(command -v nasm)" ]; then
	if [ ! -d "./nasm" ]; then
		git clone https://github.com/netwide-assembler/nasm --depth=1 --branch nasm-2.16.02rc7 nasm
		cd nasm || exit 1
		./autogen.sh
		./configure
		make "-j$THREAD_COUNT"
	fi
	export PATH="$PATH:./tools/nasm/"
fi

# build cross compiler
# assuming the compiler is new enough to not need to bootstrap
PREFIX="$ORIGIN_DIR/tools/cross-compiler"
mkdir -p "$PREFIX"
export PATH="$PREFIX/bin/:$PATH"

build_gnu_binutils() {
	cd "$TOOLS_DIR" || exit 1

	BINUTILS_DIR="binutils-cross"

	if [ ! -d "./$BINUTILS_DIR" ]; then
		mkdir -p "$BINUTILS_DIR"
	fi
	cd "$BINUTILS_DIR" || exit 1

	if [ ! -f "binutils-$BINUTILS_VERSION.tar.xz" ]; then
		wget "https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.xz"
	fi

	if [ ! -d "binutils-$BINUTILS_VERSION" ]; then
		tar -xavf "binutils-$BINUTILS_VERSION.tar.xz"
	fi

	if [ ! -f "$PREFIX/bin/$TARGET-ld" ]; then
		"./binutils-$BINUTILS_VERSION/configure" "--target=$TARGET" "--prefix=$PREFIX" --with-sysroot --disable-nls --disable-werror
		make "-j$THREAD_COUNT"
		make install
	fi
}

build_gcc() {
	cd "$TOOLS_DIR" || exit 1

	GCC_DIR="gcc-cross"

	if [ ! -d "./$GCC_DIR" ]; then
		mkdir -p "$GCC_DIR"
	fi
	cd "$GCC_DIR" || exit 1

	if [ ! -f "gcc-$GCC_VERSION.tar.xz" ]; then
		wget "https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.xz"
	fi

	if [ ! -d "gcc-$GCC_VERSION" ]; then
		tar -xavf "gcc-$GCC_VERSION.tar.xz"
	fi

	if [ ! -f "$PREFIX/bin/$TARGET-gcc" ]; then
		"./gcc-$GCC_VERSION/configure" "--target=$TARGET" "--prefix=$PREFIX" --disable-nls --enable-languages=c --without-headers
		make all-gcc "-j$THREAD_COUNT"
		make all-target-libgcc "-j$THREAD_COUNT"
		make install-gcc
		make install-target-libgcc
	fi
}

# https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm
build_llvm() {
	cd "$TOOLS_DIR" || exit 1

	if [ ! -d "./llvm-project" ]; then
		git clone https://github.com/llvm/llvm-project.git --depth=1
	fi
	cd llvm-project || exit 1
	# I really hate using cmake
	if [ ! -f "$PREFIX/bin/llvm-objcopy" ]; then
		cmake -S llvm -B build-llvm -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DLLVM_PARALLEL_COMPILE_JOBS="$(nproc)" -DLLVM_INSTALL_UTILS=ON -DCMAKE_INSTALL_PREFIX="$PREFIX"
		make -C build-llvm "-j$THREAD_COUNT"
		make -C build-llvm install
	fi
}

build_clang() {
	cd "$TOOLS_DIR" || exit 1

	if [ ! -f "$PREFIX/bin/clang" ]; then
		cmake -S clang -B build-clang -G "Unix Makefiles" -DLLVM_ROOT="$PREFIX" -DLLVM_EXTERNAL_LIT=build-llvm/utils/lit -DLLVM_INCLUDE_TESTS=OFF -DCMAKE_INSTALL_PREFIX="$PREFIX"
		make -C build-clang -j 1 # runs out of ram when linking with more than like 4 jobs
		make -C build-clang install
	fi
}

build_lld() {
	cd "$TOOLS_DIR" || exit 1

	if [ ! -f "$PREFIX/bin/lld" ]; then
		cmake -S lld -B build-lld -G "Unix Makefiles" -DLLVM_ROOT="$PREFIX" -DLLVM_EXTERNAL_LIT=build-llvm/utils/lit -DCMAKE_INSTALL_PREFIX="$PREFIX"
		make -C build-lld "-j$THREAD_COUNT"
		make -C build-lld install
	fi
}

if [ "$TOOLCHAIN" = "llvm" ]; then
	cd "$TOOLS_DIR" || exit 1
	if [ -z "$(command -v "$TARGET-ld")" ]; then
		echo -e "\n\nthe llvm toolchain needs the gnu toolchain to be built first because I can't figure out why ld.lld isn't working.\nedit the toolchain in config.sh to gnu and rebuild the os, and then try building it with llvm.\n\n"
		sleep 5
		build_gnu_binutils
	fi
	if [ -z "$(command -v llvm-objcopy)" ]; then
		build_llvm
	fi
	if [ -z "$(command -v clang)" ]; then
		build_clang
	fi
	#if [ -z "$(command -v lld)" ]; then
	#	build_lld
	#fi
	export CC="clang"
	#export LD="ld.lld"
	export LD="$TARGET-ld"
	export OBJCOPY="llvm-objcopy"
	export CFLAGS="--target=i686-pc-none-elf"
elif [ $TOOLCHAIN = "gnu" ]; then
	build_gnu_binutils
	build_gcc

	export PATH="$PATH:$PREFIX/bin/"
	export CC="$TARGET-gcc"
	export LD="$TARGET-ld"
	export OBJCOPY="$TARGET-objcopy"

fi

if [ -z "$(command -v $CC)" ]; then
	echo "cross compiler not found"
	exit 1
fi

cd "$ORIGIN_DIR" || exit 1

