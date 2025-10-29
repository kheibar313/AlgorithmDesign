#ifndef READ_PRINTMATRIX_HPP
#define READ_PRINTMATRIX_HPP

#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>
#include "si4Float.hpp"

template <typename type>
std::pair<int, int> readMatrix(std::vector<std::vector<type>> &matrix, bool inverseMatrix)
{
    int rows, cols;
    if (!inverseMatrix)
    {
        std::cout << "\nMatrix size (rows x cols)\nEnter rows: ";
        std::cin >> rows;
        std::cout << "Enter cols: ";
        std::cin >> cols;
    }
    else
    {
        std::cout << "\nMatrix size (rows x cols)\nEnter n: ";
        std::cin >> rows;
        cols = rows;
    }

    matrix.assign(rows, std::vector<type>(cols));
    std::cout << "\nEnter matrix elements row by row:\n";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            long double temp;
            std::cin >> temp;
            matrix[i][j] = si4Float(temp);
        }

    return {rows, cols};
}

template <typename type>
void printMatrix(const std::vector<std::vector<type>> &matrix, const std::pair<int, int> &size)
{
    int rows = size.first, cols = size.second;
    std::cout << std::fixed << std::setprecision(3);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            std::cout << std::setw(10) << matrix[i][j];
        std::cout << '\n';
    }
}

#endif