#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using type = double;
std::vector<std::vector<type>> mainMatrix;

namespace SI4
{
    using namespace std;
    using type = double;
    constexpr type EPS = 1e-9;

    inline bool isZero(type x) { return fabs(x) < EPS; }

    vector<int> readMatrix(vector<vector<type>> &matrix)
    {
        int rows, cols;
        cout << "\nMatrix size (rows × cols)\nEnter rows: ";
        cin >> rows;
        cout << "Enter cols: ";
        cin >> cols;

        matrix.assign(rows, vector<type>(cols));
        cout << "\nEnter matrix elements row by row:\n";
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                cin >> matrix[i][j];

        return {rows, cols};
    }

    void printMatrix(const vector<vector<type>> &matrix, const vector<int> &size)
    {
        int rows = size[0], cols = size[1];
        cout << fixed << setprecision(3);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                cout << setw(10) << matrix[i][j];
            cout << '\n';
        }
    }

    void swapRows(vector<vector<type>> &matrix, int r1, int r2)
    {
        if (r1 != r2 && r1<matrix.size() && r2<matrix.size())
            swap(matrix[r1], matrix[r2]);
    }

    bool normalizePivotRow(vector<vector<type>> &matrix, int pivotRow, int pivotCol)
    {
        type pivot = matrix[pivotRow][pivotCol];
        if (isZero(pivot))
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

    bool toEchelonForm(vector<vector<type>> &matrix, const vector<int> &size)
    {
        int rows = size[0], cols = size[1];
        int pivotRow = 0;

        for (int pivotCol = 0; pivotCol < cols && pivotRow < rows; pivotCol++)
        {
            int nonZeroRow = -1;
            for (int i = pivotRow; i < rows; i++)
            {
                if (!isZero(matrix[i][pivotCol]))
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
    auto size = SI4::readMatrix(mainMatrix);

    std::cout << "\nOriginal Matrix:\n";
    SI4::printMatrix(mainMatrix, size);

    SI4::toEchelonForm(mainMatrix, size);

    std::cout << "\nEchelon Form:\n";
    SI4::printMatrix(mainMatrix, size);

    return 0;
}
