#include <iostream>
#include <vector>

namespace my_priority_queue
{
    template <class T>
    class less
    {
    public:
        bool operator()(T a, T b)
        {
            return a < b;
        }
    };
    template <class T>
    class greate
    {
    public:
        bool operator()(T a, T b)
        {
            return a > b;
        }
    };
    template <class T, class Container = std::vector<T>, class Compare = less<T>>
    class priority_queue
    {
    private:
        void upBuild()
        {
            int child = _arr.size() - 1;
            int parent = (child - 1) / 2;
            while (child > 0)
            {
                if (_compare(_arr[child], _arr[parent]))
                    std::swap(_arr[child], _arr[parent]);
                else
                    return;
                child = parent;
                parent = (child - 1) / 2;
            }
        }
        void downBuild()
        {
            int parent = 0;
            int child = parent * 2 + 1;
            while (child < _arr.size())
            {
                if ((child + 1) < _arr.size() && _compare(_arr[child + 1], _arr[child]))
                    child++;
                if (_compare(_arr[child], _arr[parent]))
                    std::swap(_arr[parent], _arr[child]);
                else
                    return;
                parent = child;
                child = parent * 2 + 1;
            }
        }

    public:
        void push(T data)
        {
            _arr.push_back(data);
            upBuild();
        }
        void pop()
        {
            std::swap(_arr[0], _arr[_arr.size() - 1]);
            _arr.pop_back();
            downBuild();
        }
        T top()
        {
            return _arr[0];
        }
        size_t size()
        {
            return _arr.size();
        }
        bool empty()
        {
            return _arr.size() == 0;
        }

    private:
        Container _arr;
        Compare _compare;
    };
};
int main()
{
    my_priority_queue::priority_queue<int> heap;
    srand(time(NULL));
    for (int i = 0; i < 20; i++)
    {
        heap.push(rand() % 100);
    }
    while (!heap.empty())
    {
        std::cout << heap.top() << std::endl;
        heap.pop();
    }
    return 0;
}