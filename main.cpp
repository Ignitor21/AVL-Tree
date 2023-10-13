#include <iostream>
#include "avl.hpp"

using namespace avl;

int main()
{
    AVLTree tree{};
    tree.insert(1);
    tree.tree_dump();
    tree.insert(2);
    tree.tree_dump();
    tree.insert(3);
    tree.tree_dump();
    return 0;
}