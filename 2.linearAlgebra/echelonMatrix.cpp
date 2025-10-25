#include <iostream>
#include <vector>
#include <cmath>
#include "read_printMatrix.hpp"
#include "si4Float.hpp"

using type = si4Float;
std::vector<std::vector<type>> mainMatrix;

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

    void eliminateLowerRows(vector<vector<type>> &matrix, int pivotRow, int pivotCol, int rows, int cols)
    {
        for (int i = pivotRow + 1; i < rows; i++)
        {
            type factor = matrix[i][pivotCol];
            for (int j = pivotCol; j < cols; j++)
                matrix[i][j] -= factor * matrix[pivotRow][j];
        }
    }

    bool toEchelonForm(vector<vector<type>> &matrix, std::pair<int, int> &size)
    {
        unsigned rows = size.first, cols = size.second;
        unsigned pivotRow = 0;

        for (unsigned pivotCol = 0; pivotCol < cols && pivotRow < rows; pivotCol++)
        {
            int nonZeroRow = -1;
            for (unsigned i = pivotRow; i < rows; i++)
            {
                // if (!isZero(matrix[i][pivotCol]))
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
            eliminateLowerRows(matrix, pivotRow, pivotCol, rows, cols);

            pivotRow++;
        }
        return true;
    }
}

int main()
{
    auto size = readMatrix<type>(mainMatrix);

    std::cout << "\nOriginal Matrix:\n";
    printMatrix<type>(mainMatrix, size);

    SI4::toEchelonForm(mainMatrix, size);

    std::cout << "\nEchelon Form:\n";
    printMatrix<type>(mainMatrix, size);

    return 0;
}
