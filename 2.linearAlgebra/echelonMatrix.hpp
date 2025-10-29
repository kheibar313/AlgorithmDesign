#ifndef ECHELONMATRIX_HPP
#define ECHELONMATRIX_HPP

#include <vector>
#include "si4Float.hpp"

namespace SI4
{
    using namespace std;
    using type = si4Float;
    constexpr long double EPS = 1e-9;

    void swapRows(vector<vector<type>> &matrix, unsigned r1, unsigned r2)
    {
        if (r1 != r2 && r1 < matrix.size() && r2 < matrix.size())
            swap(matrix[r1], matrix[r2]);
    }

    bool normalizePivotRow(vector<vector<type>> &matrix, int pivotRow, int pivotCol)
    {
        type pivot = matrix[pivotRow][pivotCol];

        if (pivot.returnNumerator() == 0)
            return false;

        for (auto &val : matrix[pivotRow])
            val /= pivot;

        return true;
    }

    void eliminateRows(vector<vector<type>> &matrix, int pivotRow, int pivotCol, int rows, int cols)
    {
        if (matrix[0].size() == 2 * matrix.size())
            cols = matrix[0].size();

        for (int i = 0; i < pivotRow; i++)
        {
            type factor = matrix[i][pivotCol];
            for (int j = pivotCol; j < cols; j++)
                matrix[i][j] -= factor * matrix[pivotRow][j];
        }

        for (int i = pivotRow + 1; i < rows; i++)
        {
            type factor = matrix[i][pivotCol];
            for (int j = pivotCol; j < cols; j++)
                matrix[i][j] -= factor * matrix[pivotRow][j];
        }
    }

    void eliminateLowerRows(vector<vector<type>> &matrix, int pivotRow, int pivotCol, int rows, int cols)
    {
        for (int i = pivotRow + 1; i < rows; i++)
        {
            type factor = matrix[i][pivotCol];
            for (int j = pivotCol; j < cols; j++)
                matrix[i][j] -= factor * matrix[pivotRow][j];
        }
    }

    bool toEchelonForm(vector<vector<type>> &matrix, std::pair<int, int> &size, bool rref)
    {
        unsigned rows = size.first, cols = size.second;
        unsigned pivotRow = 0;

        for (unsigned pivotCol = 0; pivotCol < cols && pivotRow < rows; pivotCol++)
        {
            int nonZeroRow = -1;
            for (unsigned i = pivotRow; i < rows; i++)
            {
                if (matrix[i][pivotCol].returnNumerator() != 0)
                {
                    nonZeroRow = i;
                    break;
                }
            }

            if (nonZeroRow == -1)
                continue;

            swapRows(matrix, pivotRow, nonZeroRow);
            normalizePivotRow(matrix, pivotRow, pivotCol);

            if (rref)
                eliminateRows(matrix, pivotRow, pivotCol, rows, cols);
            else
                eliminateLowerRows(matrix, pivotRow, pivotCol, rows, cols);

            pivotRow++;
        }
        return true;
    }

    bool isZeroRow(vector<type> &row, unsigned over)
    {
        unsigned sz = row.size();
        if (over > sz)
        {
            // throw
            return false;
        }
        for (unsigned i = 0; i < over; i++)
        {
            if (row[i].returnNumerator() != 0)
                return false;
        }
        return true;
    }

    bool toInverse(vector<vector<type>> &matrix, std::pair<int, int> &size)
    {
        if (size.first != size.second)
        {
            std::cout << "Error: Matrix must be square for inverse.\n";
            return false;
        }

        int n = size.first;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    matrix[i].push_back(1);
                else
                    matrix[i].push_back(0);
            }
        }

        toEchelonForm(matrix, size, true);
        bool invertible = true;
        for (int i = 0; i < n; i++)
        {
            if (matrix[i][i].returnNumerator() == 0)
            {
                invertible = false;
                break;
            }
        }

        if (!invertible)
        {
            std::cout << "Matrix is singular - no inverse exists\n";
            return false;
        }

        for (int i = 0; i < n; i++)
        {
            matrix[i].erase(matrix[i].begin(), matrix[i].begin() + (n));
        }

        std::cout << "\nInverse Matrix Form:\n";
        return true;
    }
}

#endif