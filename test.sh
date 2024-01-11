#!/bin/sh

set -xe

qemu-system-i386 \
	-chardev stdio,id=char0,mux=on,signal=off \
	-serial chardev:char0 \
	-s \
	-drive format=raw,file=build/os.bin,media=disk
	

