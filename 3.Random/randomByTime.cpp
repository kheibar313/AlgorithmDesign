#include <chrono>
#include <iostream>

int si4Random(unsigned digits)
{
    using namespace std::chrono;

    auto now = steady_clock::now().time_since_epoch().count();

    long long last8 = now % 100000000;
    last8 /= 100;

    long long mod = 1;
    for (unsigned i = 0; i < digits; ++i)
        mod *= 10;

    int result = static_cast<int>(last8 % mod);

    return result;
}

/*
int main()
{
    unsigned int i = 0;
    long long int sum = 0, delay = 0;

    const int it = 10000;

    while (i < it)
    {
        long int start = std::chrono::steady_clock::now().time_since_epoch().count();
        long int rand2 = si4Random(2);
        std::cout << rand2 << '\n';
        long int end = std::chrono::steady_clock::now().time_since_epoch().count();
        sum += rand2;
        delay += (end - start);
        i++;
    }

    std::cout << "\n"
              << static_cast<double>(sum) / it << "\n";
    std::cout << static_cast<double>(delay) / it;
}
*/
