#include <vector>
#include <iostream>
#include "..\3.Random\makeRandomVector.hpp"

bool moveElement(std::vector<std::vector<int>> &rods, int value, int rod02, int rod03, int &stack, unsigned n)
{
    if (rods[rod02].empty() || rods[rod02].back() > value)
    {
        rods[rod02].push_back(value);
        if (rod02 == 0 && n - value == rods[rod02].size() - 1)
        {
            stack++;
        }
        return true;
    }
    else if (rods[rod03].empty() || rods[rod03].back() > value)
    {
        rods[rod03].push_back(value);
        if (rod03 == 0 && n - value == rods[rod03].size() - 1)
        {
            stack++;
        }
        return true;
    }
    return false;
}

bool moveOtherRod(std::vector<std::vector<int>> &rods, int &stack, int rod01, int rod02, int rod03, unsigned n)
{
    if (stack == n)
    {
        return true;
    };

    int begin = 0;
    if (rod01 == 0)
    {
        begin = stack;
    }

    for (int i = rods[rod01].size() - 1; i >= begin; i--)
    {
        if (moveElement(rods, rods[rod01][i], rod02, rod03, stack, n))
        {
            rods[rod01].erase(rods[rod01].begin() + i);
            continue;
        }
        break;
    }

    return true;
}

bool solveHanoi(std::vector<std::vector<int>> &rods, int &stack, unsigned n)
{
    if (stack == n)
        return true;

    moveOtherRod(rods, stack, 0, 1, 2, n);
    moveOtherRod(rods, stack, 1, 2, 0, n);
    moveOtherRod(rods, stack, 2, 0, 1, n);

    return solveHanoi(rods, stack, n);
}

int main()
{
    int n = 4;
    // const int n = 4;
    int stack = 0;
    std::cout << "Enter n: ";
    std::cin >> n;

    std::vector<int> rod1 = {};
    std::vector<int> rod2 = {};
    std::vector<int> rod3 = {};

    makeRandomListNotDuplicateCount(rod1, 1, n + 1, n);
    std::vector<std::vector<int>> rods = {rod1, rod2, rod3};

    for (int i = 0; i < 3; i++)
    {
        std::cout << "\n rod[" << i + 1 << "]: ";
        for (int j = 0; j < rods[i].size(); j++)
        {
            std::cout << rods[i][j] << ", ";
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (rod1[i] == n - i)
            stack++;
        else
            break;
    }

    solveHanoi(rods, stack, n);

    for (int i = 0; i < 3; i++)
    {
        std::cout << "\n rod[" << i + 1 << "]: ";
        for (int j = 0; j < rods[i].size(); j++)
        {
            std::cout << rods[i][j] << ", ";
        }
    }

    return 0;
}