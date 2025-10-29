#ifndef COMPARESORT_HPP
#define COMPARESORT_HPP

#include <random>
#include <chrono>
#include <iostream>
#include <vector>
#include "mainIncludeSort.hpp"

int mainCompareSort(std::vector<bool (*)(std::vector<int> &)> &algorithms, long long int delay[6], unsigned numberStartList, unsigned numberEndList)
{
    if (numberStartList >= numberEndList)
    {
        std::cout << "Start and End had problem!\n";
        return -1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::vector<int>> listOfLists;

    for (unsigned i = numberStartList; i < numberEndList; ++i)
    {
        std::uniform_int_distribution<int> dist(0, i);
        std::vector<int> list;
        for (unsigned j = 0; j < i; ++j)
            list.push_back(dist(gen));
        listOfLists.push_back(list);
    }

    std::vector<int> sortFunctionIndex = {0, 1, 2, 3, 4, 5};

    while (!sortFunctionIndex.empty())
    {
        std::uniform_int_distribution<int> dist(0, sortFunctionIndex.size() - 1);
        unsigned sFIndex = dist(gen);
        auto func = algorithms[sortFunctionIndex[sFIndex]];

        long long intDelay = 0;
        for (unsigned i = 0; i < listOfLists.size(); ++i)
        {
            auto start = std::chrono::steady_clock::now();
            func(listOfLists[i]);
            auto end = std::chrono::steady_clock::now();
            intDelay += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }

        delay[sortFunctionIndex[sFIndex]] = intDelay;
        sortFunctionIndex.erase(sortFunctionIndex.begin() + sFIndex);
    }

    return 0;
}

int compareSort()
{
    long long delay[6] = {0};
    unsigned start = 50, end = 100;
    std::cout << "Enter start: ";
    std::cin >> start;

    std::cout << "Enter end: ";
    std::cin >> end;

    mainCompareSort(Sort::menuFunctions, delay, start, end);

    auto algorithmName = Sort::menu;

    for (int i = 0; i < 5; i++)
    {
        unsigned int minIndex = i;
        for (int j = i + 1; j < 6; j++)
        {
            if (delay[minIndex] > delay[j])
            {
                minIndex = j;
            }
        }
        auto _temp = delay[i];
        delay[i] = delay[minIndex];
        delay[minIndex] = _temp;

        auto __temp = algorithmName[i];
        algorithmName[i] = algorithmName[minIndex];
        algorithmName[minIndex] = __temp;
    }

    for (int i = 0; i < 6; i++)
    {
        std::cout << "Sort[" << i << "]:" << algorithmName[i] << "\t" << delay[i] << " ns\n";
    }

    return 0;
}

#endif