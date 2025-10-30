#include <iostream>

void move(int n, char from, char to, char aux)
{
    if (n == 1)
    {
        std::cout << "Move disk 1 from " << from << " to " << to << "\n";
        return;
    }

    move(n - 1, from, aux, to);      // move n-1 from source to aux
    std::cout << "Move disk " << n << " from " << from << " to " << to << "\n";
    move(n - 1, aux, to, from);      // move n-1 from aux to target
}

int main()
{
    int n;
    std::cout << "Enter number of disks: ";
    std::cin >> n;

    move(n, 'A', 'C', 'B'); // rods: A=source, B=aux, C=target
    return 0;
}
