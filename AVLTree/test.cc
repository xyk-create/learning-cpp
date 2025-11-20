#include <iostream>
#include "tree.hpp"
int main()
{
    AVLTree<int> tree;
    srand(time(NULL));
    for (int i = 0; i < 30; i++)
        tree.insert(rand() % 100 + 1);
    std::cout<<tree._IsBalanceTree(tree.get_root())<<std::endl;
    tree._InOrder(tree.get_root());
    std::cout<<std::endl;
    return 0;
}