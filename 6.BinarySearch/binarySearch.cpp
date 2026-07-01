#include <iostream>
#include <vector>

template <typename T>
int binarySearch(std::vector<T> array, T value, int size = 0)
{
    if (size == 0)
    {
        size = array.size();
    }

    if (size <= 0)
    {
        return -2;
    }

    int left = 0;
    int right = size - 1;
    while (left <= right)
    {
        // delete this:
        // std::cout << "left = " << left << "  right = " << right << '\n';

        if (array[(left+right)/2] == value)
        {
            return (left+right)/2;
        }
        else if (array[(left+right)/2] > value)
        {
            right = (left+right)/2 - 1;
        }
        else
        {
            left = (left+right)/2 + 1;
        }
    }

    return -1;
}

int main() 
{   
    using namespace std;

    int n;
    vector<int> array{};
        
    cout << "Enter size of array: ";
    cin >> n;
    for (int i=0; i<n; i++) 
    {
        int temp;
        cout << "Enter array[" << i << "]: ";
        cin >> temp;
        array.push_back(temp);
    }

    while (true)
    {
        int value = 0;
        cout << "Enter value: ";
        cin >> value;

        int bs = binarySearch(array, value, n);
        if (bs == -1)
            cout << value << " Not found in array !! \n\n";
        else if (bs == -2)
            cout << " You're array is empty !! \n\n";
        else
            cout << value << " Found in array[" << bs <<"] . \n\n";
    }

    return 0;
}