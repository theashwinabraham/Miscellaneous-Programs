/*
* AUTHOR: ASHWIN ABRAHAM
*/
//note: These algorithms have been made only for integer arrays

#include <cstdlib>
#include "sort.hpp"

void sort::swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void sort::bubblesort(int arr[], int end, int begin /*= 0*/)
{
    if ((end - begin) <= 1)
        return;
    bool sorted = true;
    for (int i = begin; i < end - 1; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            sorted = false;
            sort::swap(arr[i], arr[i + 1]);
        }
    }
    if (sorted)
        return;
    sort::bubblesort(arr, end - 1, begin);
}

void sort::selectionsort(int arr[], int end, int begin /*= 0*/)
{
    if ((end - begin) <= 1)
        return;
    int maxind = begin;
    for (int i = 1 + begin; i < end; ++i)
    {
        if (arr[i] > arr[maxind])
        {
            maxind = i;
        }
    }
    sort::swap(arr[maxind], arr[end - 1]);
    sort::selectionsort(arr, end - 1);
}

void sort::insertionsort(int arr[], int end, int begin /*= 0*/)
{
    for (int i = begin; i < end; ++i)
    {
        int j;
        for (j = begin; j < i; ++j)
        {
            if (arr[j] > arr[i])
                break;
        }
        int temp = arr[i];
        for (int k = i; k > j; --k)
            arr[k] = arr[k - 1];
        arr[j] = temp;
    }
}

void sort::countingsort(int arr[], int end, int begin /*= 0*/)
{
    if ((end - begin) <= 1)
        return;
    int min = arr[begin], max = arr[begin];
    for (int i = 1 + begin; i < end; ++i)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
    int book[max - min + 1] = {};
    for (int i = begin; i < end; ++i)
        ++book[arr[i] - min];
    for (int i = min, k = begin; i <= max; ++i, k += book[i - min])
    {
        for (int j = 0; j < book[i - min]; ++j)
            arr[j + k] = i;
    }
}

void sort::mergesort(int arr[], int end, int begin /*= 0*/)
{
    if ((end - begin) <= 1)
        return;
    sort::mergesort(arr, (begin + end) / 2, begin);
    sort::mergesort(arr, end, (begin + end) / 2);
    int kl = begin, kr = (begin + end) / 2;
    int sortedarr[end - begin];
    for (int i = 0; i < (end - begin); ++i)
    {
        if (kl < (begin + end) / 2)
        {
            if (kr < end)
            {
                if (arr[kl] < arr[kr])
                {
                    sortedarr[i] = arr[kl];
                    ++kl;
                }
                else
                {
                    sortedarr[i] = arr[kr];
                    ++kr;
                }
            }
            else
            {
                sortedarr[i] = arr[kl];
                ++kl;
            }
        }
        else if (kr < end)
        {
            sortedarr[i] = arr[kr];
            ++kr;
        }
        else
            break;
    }
    for (int i = begin; i < end; ++i)
        arr[i] = sortedarr[i - begin];
}

void sort::quicksort(int arr[], int end, int begin /*= 0*/)
{
    if ((end - begin) <= 1)
        return;
    int pivot = begin + rand() % (end - begin), num_less = 0;
    for (int i = begin; i < end; ++i)
    {
        if (arr[i] < arr[pivot])
        {
            sort::swap(arr[i], arr[begin + num_less]);
            if (begin + num_less == pivot)
                pivot = i;
            ++num_less;
        }
    }
    sort::swap(arr[begin + num_less], arr[pivot]);
    sort::quicksort(arr, begin + num_less, begin);
    sort::quicksort(arr, end, begin + num_less + 1);
}

bool sort::binarysearch(int arr[], int search, int end, int begin /*= 0*/)
{
    if (end <= begin)
        return false;
    if (end - begin == 1)
        return arr[begin] == search;
    if (arr[(begin + end) / 2] <= search)
        return sort::binarysearch(arr, search, end, (begin + end) / 2);
    return sort::binarysearch(arr, search, (begin + end) / 2, begin);
}

int sort::upperlim(int arr[], int search, int end, int begin /*= 0*/)
{
    if (arr[begin] > search || end <= begin)
        return begin - 1;
    int pos = begin;
    for (int step = (end - begin) / 2; step > 0; step /= 2)
    {
        while (pos + step < end && arr[pos + step] <= search)
            pos += step;
    }
    return pos;
}

int sort::lowerlim(int arr[], int search, int end, int begin /*= 0*/)
{
    if (arr[end] < search || end <= begin)
        return end;
    int pos = end - 1;
    for (int step = (end - begin) / 2; step > 0; step /= 2)
    {
        while (pos - step >= begin && arr[pos - step] >= search)
            pos -= step;
    }
    return pos;
}
