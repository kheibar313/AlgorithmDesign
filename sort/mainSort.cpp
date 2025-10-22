#include "sortFiles.hpp"
#include <string>

int main()
{
    std::vector<int> arr = {1, 3, 7, 9, 2, 4, 5, 0, 6, 8};
    std::vector<std::string> menu = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort"};
    std::vector<bool (*)(std::vector<int> &, int)> menuFunctions = {bubbleSort, selectionSort, insertionSort, mergeSort};
    const int size = arr.size();

    std::cout << "Choose your function sort: \n";
    for (unsigned int i = 0; i < menu.size(); i++)
    {
        std::cout << "\n"
                  << i + 1 << "). " << menu[i];
    }

    int chose;
    std::cout << std::endl
              << std::endl
              << "Enter your chose: ";
    std::cin >> chose;

 /*   std::cout << "------" << menu[chose - 1] << "------" << std::endl
              << "A, array Before sorting: \n";*/
    std::cout << std::endl
              << "A, array Before sorting: \n";
    print(arr, arr.size());

    auto sortFunc = menuFunctions[chose - 1];
    sortFunc(arr, size);

    std::cout << "A, array After sorting: \n";
    print(arr, arr.size());
    std::cout << std::endl
              << std::endl;

    return 0;
}
