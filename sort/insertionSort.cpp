#include <vector>

bool insertionSort(std::vector<int>& arr, int size)
{
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