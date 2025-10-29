#ifndef LINEARALGEBRAOUTPUT_HPP
#define LINEARALGEBRAOUTPUT_HPP

#include "mainIncludeLinearAlgebra.hpp"

int linearAlgebraOutput()
{
    std::vector<std::vector<si4Float>> mainMatrix;
    using type = si4Float;

    unsigned choose;
    std::cout << "\n  1). REF\n  2). RREF\n  3). INVERSE\n  4). exit\n --- Enter your choose: ";
    std::cin >> choose;

    if (choose < 1 || choose > 3)
    {
        // std::cout << "Error: Invalid choice. Please enter 1, 2, or 3.\n";
        return -1;
    }

    std::pair<int, int> size;

    switch (choose)
    {
    case 1:
        size = readMatrix<type>(mainMatrix, false);
        std::cout << "\nOriginal Matrix:\n";
        printMatrix<type>(mainMatrix, size);
        SI4::toEchelonForm(mainMatrix, size, false);
        std::cout << "\nEchelon Form:\n";
        printMatrix<type>(mainMatrix, size);
        break;

    case 2:
        size = readMatrix<type>(mainMatrix, false);
        std::cout << "\nOriginal Matrix:\n";
        printMatrix<type>(mainMatrix, size);
        SI4::toEchelonForm(mainMatrix, size, true);
        std::cout << "\nReduced Echelon Form:\n";
        printMatrix<type>(mainMatrix, size);
        break;

    case 3:
        size = readMatrix<type>(mainMatrix, true);

        std::cout << "\nOriginal Matrix:\n";
        printMatrix<type>(mainMatrix, size);

        if (!SI4::toInverse(mainMatrix, size))
        {
            std::cout << "Failed to compute inverse.\n";
            return -1;
        }
        printMatrix<type>(mainMatrix, size);
        break;
    }

    return 0;
}

#endif