#include <vector>
#include "1.sort\sortOutput.hpp"
#include "2.linearAlgebra\linearAlgebraOutput.hpp"

int main()
{
    std::vector<int (*)()> outputs = {sortOutput, linearAlgebraOutput};
    std::vector<std::string> menu = {"Sort Output", "Linear Algebra Output"};
    unsigned choose = 0;

    while (true)
    {
        
        unsigned int i = 0;
        for (; i < menu.size(); i++)
        {
            std::cout << "\n   "
                      << i + 1 << "). " << menu[i];
        }
        std::cout << "\n   "
                  << i + 1 << "). " << "Exit.";
        std::cout << "\n --- Enter your chose: ";
        std::cin >> choose;
        if (choose >= i + 1)
            return 0;
        

        //choose = 2;

        auto func = outputs[choose - 1];
        std::cout << std::endl;

        func();
    }

    return true;
}