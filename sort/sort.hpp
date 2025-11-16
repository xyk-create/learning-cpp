#include <iostream>
#include <vector>
#include <functional>
namespace my_sort
{
    // void sort(std::vector<int> &arr, int begin, int end)
    // {
    //     if (begin >= end)
    //         return;
    //     int key = arr[begin];
    //     int left = begin + 1, right = end;
    //     while (left <= right)
    //     {
    //         while (left <= right && arr[left] <= key)
    //             left++;
    //         while (left <= right && arr[right] > key)
    //             right--;
    //         if (left < right)
    //             std::swap(arr[left++], arr[right--]);
    //     }
    //     std::swap(arr[begin], arr[right]);
    //     sort(arr, begin, right - 1);
    //     sort(arr, right + 1, end);
    // }
    void sort(std::vector<int> &arr, int begin, int end)
    {
        if (begin >= end)
            return;
        srand(time(NULL));
        int key = arr[rand() % (end - begin + 1) + begin];
        int left = begin - 1, right = end + 1;
        for (int i = begin; i < right; i++)
        {
            if (arr[i] < key)
                std::swap(arr[++left], arr[i]);
            else if (arr[i] > key)
                std::swap(arr[--right], arr[i--]);
        }
        sort(arr, begin, left);
        sort(arr, right, end);
    }
}

namespace my_sort
{
    void sort2(std::vector<int> &arr, int begin, int end)
    {
        if (begin >= end)
            return;
        srand(time(NULL));
        int left = begin - 1, right = end + 1;
        int key = arr[rand() % (end - begin + 1) + begin];
        for (int i = begin; i < right; i++)
        {
            if (arr[i] < key)
                std::swap(arr[++left], arr[i]);
            else if (arr[i] > key)
                std::swap(arr[--right], arr[i--]);
        }
        sort2(arr, begin, left);
        sort2(arr, right, end);
    }

    template <class Iterator>
    void sort3(Iterator begin, Iterator end, std::function<bool(Iterator a, Iterator b)> compare = [](Iterator a, Iterator b)
                                             { return *a > *b; });
}