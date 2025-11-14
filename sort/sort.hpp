#include <iostream>
#include <vector>
namespace my_sort
{
    void sort(std::vector<int> &arr, int begin, int end)
    {
        if (begin >= end)
            return;
        int key = arr[begin];
        int left = begin + 1, right = end;
        while (left <= right)
        {
            while (left <= right && arr[left] <= key)
                left++;
            while (left <= right && arr[right] > key)
                right--;
            if (left < right)
                std::swap(arr[left++], arr[right--]);
        }
        std::swap(arr[begin], arr[right]);
        sort(arr, begin, right - 1);
        sort(arr, right + 1, end);
    }
    std::vector<int> MySort(std::vector<int> &arr)
    {
        sort(arr, 0, arr.size() - 1);
        return arr;
    }
}
