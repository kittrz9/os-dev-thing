# from the ground up os dev thing

this is an attempt at a small x86 operating system with a custom bootloader<br>
<br>
currently it is only capable of loading and running premade programs from the disk<br>
<br>
the current goals are to eventually make it able to create and assemble simple assembly programs within itself<br>
<br>
maybe eventualy I'll attempt to port a C compiler and make this self hosting, but it'll probably take me a while to get to that point<br>
<br>
this has not been tested on real hardware yet<br>
<br>
some very early parts of the bootloader (specifically how the stack and GDT are set up in `boot.asm`) are based on how [limine](https://limine-bootloader.org/) sets things up<br>

## building

if your host system is running linux (I haven't tested it on any other similar platforms but it might still work) you should just be able to run `build.sh` and it will download and compile the necessary tools so you don't need to make your own cross compiler<br>
<br>
to build this you will need to have installed parted, wget, a c compiler, make, and either nasm or git (`getTools.sh` can build nasm by cloning the git repo).<br>
<br>
compiling clang through `getTools.sh` will also require git and cmake<br>
<br>
you can edit `config.sh` if you wish to change the version of gcc or binutils to be downloaded, or to use the llvm toolchain instead (which still requires binutils to be built since I can't get ld.lld to work)<br>

