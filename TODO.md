# things I need to do
 - figure out how to compile programs to be ran in the os
 - figure out how userspace programs should interface with the kernel (current idea explained later in this document)
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

<hr>

# idea for how userspace programs should work
programs should be 32 bit elf files with a single section with full permissions (it's all gonna still be in kernel mode anyway so who cares).<br>
the kernel should put a structure in a known spot in memory (such as virtual address 0) with pointers to various kernel functions (such as puts and drawFilledRect).<br>
programs will be just written in assembly and assembled using nasm to avoid needing to set up any super specific toolchain<br>
programs will be given a file to include in their assembly code containing the locations of each function pointer<br>

## issues:
 - will need to update the structure each time I want to update the API, which could end up making older programs incompatible if I decide to move anything around (though most userspace programs will probably just be reassembled with each new kernel build)
 - various security issues I couldn't care less about
