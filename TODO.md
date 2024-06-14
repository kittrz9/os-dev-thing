# things I need to do
 - figure out how to actually set up pages
 - update page frame allocator (currently works but will need to be changed when I inevitably run out of mapped pages, also probably shouldn't put the linked list stuff at the start of the page)
 - figure out how to compile programs to be ran in the os
 - userspace stuff once all the above is finished
 - implement the rest of libc
 - get ld.lld in the llvm toolchain working
 - implement ATA writing and write to the filesystem
 - get it working with the `-nostdinc` compile flag
 - figure out what I'm going to actually do with the kernel (monolithic vs microkernel and stuff like that)

<hr>

# things that I don't really need to do but want to do eventually
 - UEFI booting
 - make the kernel and bootloader compatible with multiboot
