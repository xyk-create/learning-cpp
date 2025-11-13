#include <iostream>
#include <functional>
#include <vector>
namespace my_priority_queue
{

    template <class T>
    class less
    {
    public:
        bool operator()(T a, T b)
        {
            return a > b;
        }
    };
    template <class T>
    class greate
    {
    public:
        bool operator()(T a, T b)
        {
            return a < b;
        }
    };
    template <class T, class Container = std::vector<T>, class Compare = less<T>>
    class priority_queue
    {
    private:
        void upBuild()
        {
            int child = _arry.size() - 1;
            int parent = (child - 1) / 2;
            while (child > 0)
            {
                if (_compare(_arry[child], _arry[parent]))
                {
                    std::swap(_arry[child], _arry[parent]);
                }
                child = parent;
                parent = (child - 1) / 2;
            }
        }
        void downBulid()
        {
            int parent = 0;
            int child = 2 * parent + 1;
            while (child < _arry.size())
            {
                if ((child + 1) < _arry.size() && _compare(_arry[child + 1], _arry[child]))
                    child++;
                if (_compare(_arry[child], _arry[parent]))
                    std::swap(_arry[child], _arry[parent]);
                parent = child;
                child = 2 * parent + 1;
            }
        }

    public:
        void push(T data)
        {
            _arry.push_back(data);
            upBuild();
        }
        void pop()
        {
            std::swap(_arry[0], _arry[_arry.size() - 1]);
            _arry.pop_back();
            downBulid();
        }
        T top()
        {
            return _arry[0];
        }
        size_t size()
        {
            return _arry.size();
        }
        bool empty()
        {
            return _arry.size() == 0;
        }

    private:
        Container _arry;
        Compare _compare;
    };
}