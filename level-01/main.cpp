#include <iostream>
#include <vector>
#include <functional>
#include "avl.hpp"

using namespace avl;

int main()
{
    AVLTree<int, std::less<int>> tree{};
    std::vector<int> input1{20, 10, 30, 2, 14, 27, 50, 7};

    for (const auto& x: input1)
    {
        tree.insert(x);
    }

    AVLTree<int> tree2;
    std::vector<int> input2{-20, -10, -30, -2, -14, -27, -50, -7};

    for (const auto& x: input2)
    {
        tree2.insert(x);
    }

    AVLTree<int> new_tree = std::move(tree2);
    //tree.TreeDump();
    //new_tree.TreeDump();
    new_tree.TreeDump();
    
    //new_tree.TreeDump();

    std::cout << "\n";
    return 0;
}