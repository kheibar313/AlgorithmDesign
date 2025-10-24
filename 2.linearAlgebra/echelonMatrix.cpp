#include <iostream>
#include <vector>

using type = double;
std::vector<std::vector<type>> mainMatrix;

namespace SI4
{
    using namespace std;
    using type = double;

    vector<int> input(vector<vector<type>> &matrix)
    {
        int m, n;
        cout << "\nMatrix m * n\nEnter m: ";
        cin >> m;
        cout << "Enter n: ";
        cin >> n;

        matrix.clear();
        vector<int> dims = {m, n};

        cout << "\nEnter matrix elements row by row:\n";
        for (int i = 0; i < m; i++)
        {
            vector<type> row;
            for (int j = 0; j < n; j++)
            {
                type inp;
                cin >> inp;
                row.push_back(inp);
            }
            matrix.push_back(row);
        }

        return dims;
    }

    void print(vector<vector<type>> &matrix, vector<int> size)
    {
        int m = size[0], n = size[1];
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                cout << matrix[i][j] << "\t";
            cout << endl;
        }
    }

    void replace(vector<vector<type>> &matrix, int row1, int row2)
    {
        if (row1 != row2)
            swap(matrix[row1], matrix[row2]);
    }

    bool makePivot(vector<vector<type>> &matrix, int numberRow, int rowLeading, int col)
    {
        if (numberRow >= matrix.size() || matrix[numberRow].size() < 1)
            return false;

        replace(matrix, numberRow, rowLeading);

        type pivot = matrix[rowLeading][col];
        if (pivot == 0)
            return false;

        for (int i = 0; i < matrix[rowLeading].size(); i++)
            matrix[rowLeading][i] /= pivot;

        return true;
    }

    void eliminateBelow(vector<vector<type>> &matrix, int rowLeading, int col, int m, int n)
    {
        for (int i = rowLeading + 1; i < m; i++)
        {
            type factor = matrix[i][col];
            for (int j = col; j < n; j++)
                matrix[i][j] -= factor * matrix[rowLeading][j];
        }
    }

    bool echelonMatrix(vector<vector<type>> &matrix, vector<int> size)
    {
        int m = size[0], n = size[1];
        int rowLeading = 0;

        for (int col = 0; col < n && rowLeading < m; col++)
        {
            int pivotRow = -1;
            for (int i = rowLeading; i < m; i++)
            {
                if (matrix[i][col] != 0)
                {
                    pivotRow = i;
                    break;
                }
            }
            if (pivotRow == -1)
                continue;

            makePivot(matrix, pivotRow, rowLeading, col);
            eliminateBelow(matrix, rowLeading, col, m, n);

            rowLeading++;
        }
        return true;
    }
}

int main()
{
    std::vector<int> size = SI4::input(mainMatrix);

    std::cout << "\nOriginal Matrix:\n";
    SI4::print(mainMatrix, size);

    SI4::echelonMatrix(mainMatrix, size);

    std::cout << "\nEchelon Form:\n";
    SI4::print(mainMatrix, size);

    return 0;
}
