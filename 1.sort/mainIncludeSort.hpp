#ifndef MAININCLUDE_HPP
#define MAININCLUDE_HPP

#include "sortInclude.hpp"
#include "print.hpp"
#include "swap.hpp"
#include "exit.hpp"

namespace Sort
{
    std::vector<int> mainArr = {1, 3, 7, 9, 2, 4, 5, 0, 6, 8};
    std::vector<std::string> menu = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort", "Heap Sort"};
    std::vector<bool (*)(std::vector<int> &)> menuFunctions = {bubbleSort, selectionSort, insertionSort, mergeSort, quickSort, heapSort};
}

#endif