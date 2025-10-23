#ifndef EXIT_HPP
#define EXIT_HPP

#include <cstdlib>

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void eXit()
{
    exit(0);
}

#endif