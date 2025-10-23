#include "mainInclude.hpp"

namespace SI4
{
    using namespace std;

    int mainSI4()
    {
        while (true)
        {
            vector<int> arr = mainArr;
            cout << "  ---------------  Sorting Algorithms ---------------  ";

            unsigned int i = 0;
            for (; i < menu.size(); i++)
            {
                cout << "\n   "
                     << i + 1 << "). " << menu[i];
            }
            cout << "\n   "
                 << i + 1 << "). " << "Exit.";

            int chose;
            cout << "\n  --- Choose your function sort: ";
            cin >> chose;
            if (chose == 7)
                eXit();

            cout << "\n  -------------" << menu[chose - 1] << "-------------  " << endl
                 << "   Before sorting: \n     ";
            print(arr, arr.size());

            auto sortFunc = menuFunctions[chose - 1];
            sortFunc(arr);

            cout << "   After sorting: \n     ";
            print(arr, arr.size());
            cout
                << endl
                << endl;
        }
        return 0;
    }
}

int main()
{
    return SI4::mainSI4();
}