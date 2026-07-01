#ifndef SWAP_HPP
#define SWAP_HPP

template <typename T>
bool swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;

    return true;
}

#endif