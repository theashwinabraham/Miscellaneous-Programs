/*
* AUTHOR: ASHWIN ABRAHAM
*/

/*Reads the representation of an obect in memory
Endianness (bigendian, littleendian) states the order in which the bits are stored in memory

For example, call bigendian(3) to see how 3 would be stored
To know how the 3 would be stored as a float/double, call bigendian<float>(3) and bigendian<double>(3) respectively

Also if the object contains pointers this will not show the bits in the memory pointed to by these pointers*/

#ifndef _READBITS_H_
#define _READBITS_H_

#include <vector>
#define usize (8*sizeof(unsigned int))

namespace readbits{
    template <typename T>
    std::vector<bool> littleendian(const T& a)
    {
        std::vector<bool> bits;
        const unsigned int* ptra = reinterpret_cast<const unsigned int*>(&a);
        for(int i = 0; i<8*sizeof(T); ++i) bits.push_back((ptra[i/usize]>>(i%usize))&1);
        return bits;
    }

    template <typename T>
    std::vector<bool> bigendian(const T& a){
        std::vector<bool> bits;
        const unsigned int* ptra = reinterpret_cast<const unsigned int*>(&a);
        for(int i = 8*sizeof(T)-1; i>=0; --i) bits.push_back((ptra[i/usize]>>(i%usize))&1);
        return bits;
    }
}

#undef usize
#endif