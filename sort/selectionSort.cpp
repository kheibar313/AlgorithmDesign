#include <vector>
#include "swap.hpp"

bool selectionSort(std::vector<int> &arr)
{
    int size = arr.size();
    if (size <= 0) return false;
    
    int minIndex = 0;

    for (int i = 0; i < size-1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }

    return true;
}