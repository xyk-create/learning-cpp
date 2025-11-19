#include <iostream>
#include <vector>
#include <functional>
#include <climits>
namespace my_sort
{
    // void quick_sort(std::vector<int> &arr, int begin, int end)
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
    void quick_sort(std::vector<int> &arr, int begin, int end)
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
        quick_sort(arr, begin, left);
        quick_sort(arr, right, end);
    }
}

namespace my_sort
{
    void quick_sort2(std::vector<int> &arr, int begin, int end)
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
        quick_sort2(arr, begin, left);
        quick_sort2(arr, right, end);
    }

    template <class Iterator>
    void quick_sort3(Iterator begin, Iterator end, std::function<bool(Iterator a, Iterator b)> compare = [](Iterator a, Iterator b)
                                                   { return *a > *b; });
    void merge_sort(std::vector<int> &arr, int left, int right)
    {
        if (left >= right)
            return;
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        std::vector<int> tmp(arr.begin(), arr.end());
        int p1 = left, p2 = mid + 1, pos = left;
        while (p1 <= mid && p2 <= right)
        {
            if (arr[p1] <= arr[p2])
                tmp[pos++] = arr[p1++];
            else
                tmp[pos++] = arr[p2++];
        }
        while (p1 <= mid)
            tmp[pos++] = arr[p1++];
        while (p2 <= right)
            tmp[pos++] = arr[p2++];
        for (int i = left; i <= right; i++)
            arr[i] = tmp[i];
    }
    void shell_sort(std::vector<int> &arr)
    {
        int grp = arr.size();
        while (grp > 1)
        {
            grp = grp / 3 + 1;
            for (int i = 0; i < arr.size(); i++)
            {
                int tmp = arr[i], j = i;
                while (j - grp >= 0 && tmp < arr[j - grp])
                {
                    arr[j] = arr[j - grp];
                    j-=grp;
                }
                arr[j] = tmp;
            }
        }
    }
    void heap_sort(std::vector<int>& arr)
    {
        std::vector<int> heap;
        for(int i=0;i<arr.size();i++)
        {
            heap.push_back(arr[i]);
            int child = heap.size()-1;
            int parent = (child-1)/2;
            while(child>0)
            {
                if(heap[child]<=heap[parent])
                {
                    std::swap(heap[child],heap[parent]);
                    child = parent;
                    parent = (child-1)/2;
                }
                else break;
            }
            
        }  
        int i=0;
        while(!heap.empty())
        {
            std::swap(heap[0],heap[heap.size()-1]);
            arr[i++] = heap.back();
            heap.pop_back();
            int parent = 0;
            int child = parent*2+1;
            while(child<heap.size())
            {
                if(child+1<heap.size()&&heap[child+1]<heap[child])
                    child++;
                if(heap[child]<=heap[parent])
                {
                    std::swap(heap[child],heap[parent]);
                    parent = child;
                    child = parent*2+1;
                }
                else break;
            }
        }
    }
    void count_sort(std::vector<int>& arr)
    {
        int max=INT_MIN,min = INT_MAX;
        for(auto val:arr)
        {
            if(val>max) max = val;
            if(val<min) min = val; 
        }
        int tmp = max-min+1;
        std::vector<int> hash(tmp);
        for(auto val:arr)
            hash[val-min]++;
        int pos = 0;
        for(int i = 0;i<hash.size();i++)
        {
            while(hash[i]--)
                arr[pos++] = i+min;
        }
    }
}
