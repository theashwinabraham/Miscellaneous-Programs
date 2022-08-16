# Assembly Language

This repository consists of assembly language files written by me while I was learning the language as part of the [Year of Security](https://github.com/CSecIITB/module-1-c-and-asm) Programme conducted by the [Cybersecurity Club](https://github.com/CSecIITB) at IIT Bombay.

Some resources I found useful while learning Assembly Programming were:
- [The CS 216 Webpage from the University of Virginia](https://www.cs.virginia.edu/~evans/cs216/guides/x86.html)
- [The Wikibook on x86 assembly](https://en.wikibooks.org/wiki/X86_Assembly/Print_Version)
- [Some resources from the CS 301 course taught by Dr Lawlor from the University of Alaska](https://docs.google.com/document/d/1J1ZD4JbgTFrfdv_vsJBe96NcNoEwsm7LTQasWZcnMN8/edit)

# Usage Instructions
All the assembly code here was written for x86 64 bit systems running Linux.
The assembly code has been written in the Intel Syntax and is to be assembled with the [Netwide Assembler](https://www.nasm.us/) (NASM).

To get NASM in Linux, just enter:

    sudo apt install nasm
in the terminal

To assemble an x86 assembly file (named ```file.asm```, for example) in 64 bit mode, execute:

    nasm -f elf64 -g file.asm,

This will output an object file called ```file.o``` by default.

If ```file.asm``` called C library functions (such as ```main```, ```printf```, ```scanf```, etc), to create the executable we must compile and link 
the object file using a C compiler such as GCC.

    gcc file.o

Some errors may be rectified by using the ```-no-pie``` option

    gcc -no-pie file.o

```Tib.asm``` and ```clib.asm``` are to be compiled this way.


If the function instead relies solely on standard CPU instructions and System Calls, such as the ```read``` and ```write``` syscalls, then we can use the linker directly instead of GCC.

    ld -g file.o

```standalone.asm``` is to be compiled this way.

If ```file.asm``` just defines functions to be linked in a C/C++ file, we can use GCC again

    gcc file.o other_file.c

```func.asm``` is to be linked with ```linkasm.c``` in this way

In all of these examples, unless otherwise specidied ```a.out``` is the standard executable file and ```file.o``` is the object module formed after compilation/assembly.
