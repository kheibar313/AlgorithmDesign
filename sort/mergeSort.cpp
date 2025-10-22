#include <vector>
//delete this
#include <iostream>

bool realMergeSort(std::vector<int> &, int, int);
bool merge(std::vector<int> &, int, int, int);

bool mergeSort(std::vector<int> &arr, int size)
{
    //delete this
    std::cout << "mergeSort\n\n";

    if (size <= 0) return false;

    realMergeSort(arr, 0, size - 1);

    return true;
}

bool realMergeSort(std::vector<int> &arr, int low, int high)
{
    if (low >= high) return true;
    
    int mid = low + (high - low) / 2;

    realMergeSort(arr, low, mid);
    realMergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);

    return true;
}

bool merge(std::vector<int> &arr, int low, int mid, int high) {
    std::vector<int> temp;
    int left = low, right = mid + 1;
    
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left++]);
        } else {
            temp.push_back(arr[right++]);
        }
    }

    while (left <= mid) temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);
    
    for (int i = 0; i < temp.size(); i++) {
        arr[low + i] = temp[i];
    }
    
    return true;
}