#include "priority_queue.hpp"
int main()
{
    my_priority_queue::priority_queue<int> heap;
    heap.push(1);
    heap.push(9);
    heap.push(6);
    heap.push(4);
    heap.push(3);
    while(!heap.empty())
    {
        std::cout<<heap.top()<<" ";
        heap.pop();
    }
    std::cout<<std::endl;
    my_priority_queue::priority_queue<int,std::vector<int>,my_priority_queue::greate<int>> heap2;
    heap2.push(1);
    heap2.push(9);
    heap2.push(6);
    heap2.push(4);
    heap2.push(3);
    while(!heap2.empty())
    {
        std::cout<<heap2.top()<<" ";
        heap2.pop();
    }
    std::cout<<std::endl;
    return 0;
}