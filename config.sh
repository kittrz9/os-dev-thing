#!/bin/sh

# you should not need to run this
# this just sets variables for other scripts

# the llvm toolchain still needs to be fixed, ld.lld doesn't work and the framebuffer doesn't work for some reason
export TOOLCHAIN="gnu"
export TARGET="i686-elf"

# only used for building the toolchain, not building the os
export THREAD_COUNT="$(nproc)"


export BINUTILS_VERSION="2.42"
export GCC_VERSION="14.1.0"
