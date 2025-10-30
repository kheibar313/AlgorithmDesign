#ifndef MAKERANDOMVECTOR_HPP
#define MAKERANDOMVECTOR_HPP

#include <random>
#include <vector>
#include <algorithm>

bool makeRandomListListDuplicate(std::vector<int> &list, int start, int end, size_t count)
{
    if (start >= end || count == 0)
        return false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(start, end - 1);

    list.clear();
    list.reserve(count);

    for (size_t i = 0; i < count; ++i)
        list.push_back(dist(gen));

    return true;
}

bool makeRandomListNotDuplicateCount(std::vector<int> &list, int start, int end, size_t count)
{
    if (start >= end || count > static_cast<size_t>(end - start))
        return false;

    std::vector<int> temp;
    temp.reserve(end - start);
    for (int i = start; i < end; ++i)
    {
        temp.push_back(i);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(temp.begin(), temp.end(), gen);

    list.assign(temp.begin(), temp.begin() + count);

    return true;
}

#endif