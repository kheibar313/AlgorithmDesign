#ifndef SWAP_HPP
#define SWAP_HPP

bool swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;

    return true;
}

#endif