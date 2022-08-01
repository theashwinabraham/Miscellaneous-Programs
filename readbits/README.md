# Readbits - A program to see the representation of an object in memory

This is a program that will print out the representation of an object in memory, i.e, it prints out the ones and zeroes stored in the memory
that represent the object. Although in most cases the exact method of storage is irrelevant, there are some algorithms such as the
[Fast Inverse Square Root](https://en.wikipedia.org/wiki/Fast_inverse_square_root) algorithm[^1] from the game Quake III Arena, which do depend on
the method of storage of floating point variables in memory (the [IEEE 754 Floating Point Standard](https://en.wikipedia.org/wiki/IEEE_754)). Hence,
this program might help better understand how such variables are stored and how such algorithms work.


Clearly, the representation of an object in memory depends on the [endianness](https://en.wikipedia.org/wiki/Endianness) of the memory in which it is
stored. The endianness refers to whether the least significant bit is stored first or last. In little-endian storage the least significant bit is 
stored first in memory, whereas in big-endian storage it is stored last. Note that usually, variables are stored in a little-endian manner.


For example, the 32 bit unsigned integer 3, would be stored in a little-endian manner as:
> 11000000000000000000000000000000

whereas, in a big-endian manner it would be stored as:
> 00000000000000000000000000000011

## Usage Instructions
Download the file ```readbits.hpp``` and move it into the same directory as your code.

Then include the file in your C++ code (```#include "readbits.hpp"```) and call either ```readbits::littleendian``` or ```readbits::bigendian``` with your variable/literal as a parameter.


These functions return vectors containing 0s and 1s. The first entry of ```readbits::littleendian``` would be the least significant bit and the first entry of ```readbits::bigendian``` would be the most significant bit.


Since littleendian and bigendian are template functions, you can explicitly specify the type of the parameter while calling it (otherwise it would be implicitly deduced by the compiler). (For example, ```readbits::littleendian(3)``` would return the representation of 3 as an integer, whereas ```readbits::littleendian<double>(3)``` would return the representation of 3 as a double).

Note that if the object contains pointers as members then the these functions only give the representation of the pointer in memory, not the 
representation of the pointed to memory.

[^1]: This program was inspired by [this](https://www.youtube.com/watch?v=p8u_k2LIZyo) excellent YouTube video explaining how the Fast Inverse Square Root algorithm worked.