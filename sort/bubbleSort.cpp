#include <vector>
/*delete this*/#include <iostream>

bool bubbleSort(std::vector<int> &arr, int size)
{
    /*delete this*/std::cout << "bubbleSort\n\n";
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return true;
}