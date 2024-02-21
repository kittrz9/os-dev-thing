#!/bin/sh

set -xe

qemu-system-i386 \
	-enable-kvm \
	-chardev stdio,id=char0,mux=on,signal=off \
	-serial chardev:char0 \
	-s \
	-audiodev pipewire,id=asdf -machine pcspk-audiodev=asdf \
	-drive format=raw,file=build/os.bin,media=disk
	

