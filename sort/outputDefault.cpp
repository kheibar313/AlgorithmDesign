#include "mainInclude.hpp"

int main()
{
    while (true)
    {
        std::vector<int> arr = mainArr;
        std::cout << "  ---------------  Sorting Algorithms ---------------  ";

        unsigned int i = 0;
        for (; i < menu.size(); i++)
        {
            std::cout << "\n   "
                      << i + 1 << "). " << menu[i];
        }
        std::cout << "\n   "
                  << i + 1 << "). " << "Exit.";

        int chose;
        std::cout << "\n  --- Choose your function sort: ";
        std::cin >> chose;
        if (chose == 7)
            eXit();

        std::cout << "\n  -------------" << menu[chose - 1] << "-------------  " << std::endl
                  << "   Before sorting: \n     ";
        print(arr, arr.size());

        auto sortFunc = menuFunctions[chose - 1];
        sortFunc(arr);

        std::cout << "   After sorting: \n     ";
        print(arr, arr.size());
        std::cout
            << std::endl
            << std::endl;
    }

    return 0;
}