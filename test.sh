#!/bin/sh


qemu-system-x86_64 \
	-chardev stdio,id=char0,mux=on,signal=off \
	-serial chardev:char0 \
	-drive format=raw,file=build/os.bin
	

