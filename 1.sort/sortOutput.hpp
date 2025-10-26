#ifndef SORTOUTPUT_HPP
#define SORTOUTPUT_HPP

#include "mainIncludeSort.hpp"

namespace SI4
{
    using namespace std;

    int mainSI4()
    {
        while (true)
        {
            vector<int> arr = Sort::mainArr;
            cout << "  ---------------  Sorting Algorithms  ---------------  ";

            unsigned int i = 0;
            for (; i < Sort::menu.size(); i++)
            {
                cout << "\n   "
                     << i + 1 << "). " << Sort::menu[i];
            }
            cout << "\n   "
                 << i + 1 << "). " << "Exit.";

            unsigned chose;
            cout << "\n  --- Choose your function sort: ";
            cin >> chose;
            if (chose == i+1)
                //eXit();
                return 0;

            cout << "\n  -------------" << Sort::menu[chose - 1] << "-------------  " << endl
                 << "   Before sorting: \n     ";
            print(arr, arr.size());

            auto sortFunc = Sort::menuFunctions[chose - 1];
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

int sortOutput()
{
    return SI4::mainSI4();
}

#endif