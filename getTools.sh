#!/bin/sh

. ./config.sh

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
export PATH="$PREFIX/bin/:$PATH"
if [ "$TOOLCHAIN" = "llvm" ]; then
	cd "$TOOLS_DIR" || exit 1
	if [ -z "$(command -v "$TARGET-ld")" ]; then
		echo -e "\n\nthe llvm toolchain needs the gnu toolchain to be built first because I can't figure out why ld.lld isn't working.\nedit the toolchain in config.sh to gnu and rebuild the os, and then try building it with llvm.\n\nthe llvm toolchain also just doesn't work still, the framebuffer doesn't show up but serial seems to work fine.\n\n"
		exit 1
	fi
	if [ -z "$(command -v clang)" ] || [ -z "$(command -v lld)" ]; then
		# https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm
		if [ ! -d "./llvm-project" ]; then
			git clone https://github.com/llvm/llvm-project.git --depth=1
		fi
		cd llvm-project || exit 1
		# I really hate using cmake
		if [ ! -f "$PREFIX/bin/llvm-objcopy" ]; then
			cmake -S llvm -B build-llvm -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DLLVM_PARALLEL_COMPILE_JOBS="$(nproc)" -DLLVM_INSTALL_UTILS=ON -DCMAKE_INSTALL_PREFIX="$PREFIX"
			make -C build-llvm -j "$(nproc)"
			make -C build-llvm install
		fi

		if [ ! -f "$PREFIX/bin/clang" ]; then
			cmake -S clang -B build-clang -G "Unix Makefiles" -DLLVM_ROOT="$PREFIX" -DLLVM_EXTERNAL_LIT=build-llvm/utils/lit -DLLVM_INCLUDE_TESTS=OFF -DCMAKE_INSTALL_PREFIX="$PREFIX"
			make -C build-clang -j 1 # runs out of ram when linking with more than like 4 jobs
			make -C build-clang install
		fi

		if [ ! -f "$PREFIX/bin/lld" ]; then
			cmake -S lld -B build-lld -G "Unix Makefiles" -DLLVM_ROOT="$PREFIX" -DLLVM_EXTERNAL_LIT=build-llvm/utils/lit -DCMAKE_INSTALL_PREFIX="$PREFIX"
			make -C build-lld -j "$(nproc)"
			make -C build-lld install
		fi
	fi
	export CC="clang"
	#export LD="ld.lld"
	export LD="$TARGET-ld"
	export OBJCOPY="llvm-objcopy"
	export CFLAGS="--target=i686-pc-none-elf"
elif [ $TOOLCHAIN = "gnu" ]; then
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
fi

cd "$ORIGIN_DIR" || exit 1

