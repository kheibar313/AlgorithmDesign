#ifndef PRINT_HPP
#define PRINT_HPP

#include <vector>
#include <iostream>

bool print(std::vector<int> arr, int size)
{
    std::cout << "[";
    for (int i = 0; i < size - 1; i++)
    {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[size - 1] << "]\n";
    return true;
}

#endif