#include <vector>
#include "swap.hpp"

bool bubbleSort(std::vector<int> &arr)
{
    int size = arr.size();
    if (size <= 0)
        return false;

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    return true;
}