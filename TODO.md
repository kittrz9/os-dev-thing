# things I need to do
 - implement more syscalls (int 0x80 currently just prints whatever eax is pointing)
 - make loading elf files not garbage, maybe load multiple sections or something
 - add a way to map multiple pages at once
 - multitasking
 - maybe not run everything in kernel mode
 - implement the rest of libc
 - get ld.lld in the llvm toolchain working
 - implement ATA writing and write to the filesystem
 - get it working with the `-nostdinc` compile flag
 - figure out what I'm going to actually do with the kernel (monolithic vs microkernel and stuff like that)

<hr>

# things that I don't really need to do but want to do eventually
 - UEFI booting
 - make the kernel and bootloader compatible with multiboot

