#include <iostream>
#include <vector>
#include "avl.hpp"

using namespace avl;

int main()
{
    AVLTree tree{};
    std::vector<int> input{13, 14, 15, 12, 11, 17, 16, 8, 9, 1};

    for (const auto& x: input)
    {
        tree.insert(x);
        tree.tree_dump();
    }

    return 0;
}