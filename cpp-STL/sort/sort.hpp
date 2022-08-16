/*
* AUTHOR: ASHWIN ABRAHAM
*/
//note: These algorithms have been made only for integer arrays

#ifndef SORT_HPP
#define SORT_HPP
namespace sort
{
    //swaps two integers
    void swap(int &, int &);

    //these algorithms sort integer arrays
    void bubblesort(int *, int, int = 0);
    void selectionsort(int *, int, int = 0);
    void insertionsort(int *, int, int = 0);
    void countingsort(int *, int, int = 0);
    void mergesort(int *, int, int = 0);
    void quicksort(int *, int, int = 0);

    //returns whether or not an integer is present in the array
    bool binarysearch(int *, int, int, int = 0);
    // returns position of the element closest to end in the sorted array satisfying element <= parameter
    int upperlim(int *, int, int, int = 0);
    // returns position of the element closest to beginning in the sorted array satisfying element >= parameter
    int lowerlim(int *, int, int, int = 0);
}
#endif