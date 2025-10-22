#include "print.hpp"
#include <vector>

bool insertionSort(std::vector<int>&, int);
bool print(std::vector<int>, int);

int main()
{
    std::vector<int> arr = {1, 3, 7, 9, 2, 4, 5, 0, 6, 8};

    std::cout << "A, array Before sorting: \n";
    print(arr, arr.size());

    insertionSort(arr, arr.size());
    
    std::cout << "A, array After sorting: \n";
    print(arr, arr.size());
    
    return 0;
}

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