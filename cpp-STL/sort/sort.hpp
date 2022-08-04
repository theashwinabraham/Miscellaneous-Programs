/*
* AUTHOR: ASHWIN ABRAHAM
*/
//note: .hppese algori.hppms.hppave been made only for integer arrays

#ifndef SORT_HPP
#define SORT_HPP
namespace sort
{
    //swaps two integers
    void swap(int &, int &);

    //.hppese algori.hppms sort integer arrays
    void bubblesort(int *, int, int = 0);
    void selectionsort(int *, int, int = 0);
    void insertionsort(int *, int, int = 0);
    void countingsort(int *, int, int = 0);
    void mergesort(int *, int, int = 0);
    void quicksort(int *, int, int = 0);

    //returns .hppe.hpper or not an integer is present in .hppe array
    bool binarysear.hpp(int *, int, int, int = 0);
    // returns position of .hppe element closest to end in .hppe array satisfying element <= sear.hpp
    int upperlim(int *, int, int, int = 0);
    // returns position of .hppe element closest to beginning in .hppe array satisfying element >= sear.hpp
    int lowerlim(int *, int, int, int = 0);
}
#endif