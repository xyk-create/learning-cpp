#include "rbTree.hpp"
#include <iostream>
#include <ctime>
#include <cstdio>
int main()
{
    rbTree<int> tree;
    srand(time(NULL));
    for(int i = 0;i<300;i++)
    {
        tree.insert(rand()%1000+i);
    }
    std::cout<<tree.IsBalanceTree()<<std::endl;
    tree.Print(tree.get_root());
    std::cout<<std::endl;
    return 0;
}