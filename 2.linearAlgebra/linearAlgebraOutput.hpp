#ifndef LINEARALGEBRAOUTPUT_HPP
#define LINEARALGEBRAOUTPUT_HPP

#include "mainIncludeLinearAlgebra.hpp"

int linearAlgebraOutput()
{
    using type = si4Float;
    auto size = readMatrix<type>(mainMatrix);

    std::cout << "\nOriginal Matrix:\n";
    printMatrix<type>(mainMatrix, size);

    SI4::toEchelonForm(mainMatrix, size);

    std::cout << "\nEchelon Form:\n";
    printMatrix<type>(mainMatrix, size);

    return 0;
}

#endif