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
        //tree.tree_dump();
    }

    AVLNode* node = tree.find_by_number(10);
    if(node)
    {
        std::cout << node->key << "\n";
    }
    else
    {
        std::cout << "Not found\n";
    }
    
    return 0;
}