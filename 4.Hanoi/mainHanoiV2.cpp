#include <iostream>
#include <vector>

void print(std::vector<std::vector<int>> &rods)
{
    for (int i = 0; i < 3; i++)
    {
        std::cout << "[" << i + 1 << "]: ";

        if (rods[i].size() > 0)
            std::cout << rods[i][0];
        for (int j = 1; j < rods[i].size(); j++)
        {
            std::cout << ", " << rods[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

bool moveElement(std::vector<std::vector<int>> &rods, int from, int to)
{
    int r0Size = rods[from].size();
    int disk;
    if (r0Size > 0)
        disk = rods[from][r0Size - 1];
    else
        return false;
    rods[from].pop_back();
    rods[to].push_back(disk);
    print(rods);
    return true;
}

bool move(std::vector<std::vector<int>> &rods, int index, int from, int aux, int to)
{
    if (index == 1)
        return moveElement(rods, from, to);

    move(rods, index - 1, from, to, aux);
    moveElement(rods, from, to);
    print(rods);
    move(rods, index - 1, aux, from, to);

    return true;
}

int main()
{
    int n = 4;
    std::vector<int> rod1;
    std::vector<int> rod2;
    std::vector<int> rod3;
    std::vector<std::vector<int>> rods = {rod1, rod2, rod3};

    std::cout << "Enter n: ";
    std::cin >> n;

    for (int i = n; i > 0; i--)
        rods[0].push_back(i);

    move(rods, n, 0, 1, 2);

    return 0;
}