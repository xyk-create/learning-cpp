#include "hashTable.hpp"

int main()
{
    HashTable<int, int> table;
    for(int i = 0; i < 1000000; i++)
    {
        table.insert(std::make_pair(i,i-1));
    }
    for(int i = 0; i < 100000; i++)
    {
        std::cout<<table[i]<<" ";
    }
    return 0;
}