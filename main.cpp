#include <iostream>
#include "avl.hpp"

using namespace avl;

int main()
{
    AVLTree* tree = new AVLTree{};
    tree->insert(2);
    tree->insert(1);
    tree->insert(3);

    print_subtree(tree->root);
    std::cout << "\n";
    return 0;
}