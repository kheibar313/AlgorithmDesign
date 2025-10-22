#include <vector>

bool bubbleSort(std::vector<int> &arr, int size)
{
    int min = arr[0], minIndex = 0;

    for (int i = 0; i < size; i++)
    {
        min = arr[i], minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < min){
                min = arr[j];
                minIndex = j;
            }
        }
    }

    return true;
}