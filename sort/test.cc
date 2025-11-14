#include <iostream>
#include <vector>
#include "sort.hpp"
#define SIZE 20
int main()
{
    srand(time(NULL));
    std::vector<int> arr(SIZE);
    for (int i = 0; i < arr.size(); i++)
        arr[i] = rand() % 1000;
    my_sort::sort(arr, 0, arr.size());
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
        if ((i+1) % 5 == 0)
            std::cout << std::endl;
    }
    return 0;
}
