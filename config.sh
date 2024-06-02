#!/bin/sh

# you should not need to run this
# this just sets variables for other scripts

# the llvm toolchain still needs to be fixed, ld.lld doesn't work and the framebuffer doesn't work for some reason
export TOOLCHAIN="llvm"
export TARGET="i686-elf"
