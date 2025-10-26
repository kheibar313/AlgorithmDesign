#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP

#include <vector>

bool insertionSort(std::vector<int>& arr)
{
    int size = arr.size();
    if (size <= 0) return false;

    for (int i = 1; i < size; i++)
    {
        int now = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > now)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = now;
    }
    return true;
}

#endif