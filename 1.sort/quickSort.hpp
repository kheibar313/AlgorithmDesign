#ifndef QUICKSORT
#define QUICKSORT

#include <vector>
#include "swap.hpp"
#include <cstdlib>

int partition(std::vector<int> &arr, int low, int high)
{
    int randomIndex = low + rand() % (high - low);
    swap(arr[low], arr[randomIndex]);

    int pivot = arr[low];
    int lowIndex = low + 1;

    for (int i = low + 1; i < high; i++)
    {
        if (arr[i] < pivot)
        {
            swap(arr[i], arr[lowIndex]);
            lowIndex++;
        }
    }

    swap(arr[low], arr[lowIndex - 1]);

    return lowIndex-1;
}

bool realQuickSort(std::vector<int> &arr, int low, int high)
{
    if (low >= high)
        return true;

    int pivot = partition(arr, low, high);
    realQuickSort(arr, low, pivot);
    realQuickSort(arr, pivot + 1, high);

    return true;
}

bool quickSort(std::vector<int> &arr)
{
    int size = arr.size();
    if (size < 1)
        return false;
    realQuickSort(arr, 0, size);

    return true;
}

#endif