#include <vector>
/*delete this*/#include <iostream>

bool selectionSort(std::vector<int> &arr, int size)
{
    /*delete this*/std::cout << "selection sort\n\n";
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
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }

    return true;
}