#include <iostream>
#include <vector>
#include <functional>
#include "avl.hpp"

using namespace avl;

int main()
{
    AVLTree<int> tree{};
    int n{};
    char command{};

    while(std::cin >> command >> n)
    {
        switch (command)
        {
        case 'k':
            tree.insert(n);
            break;
        case 'm':
        {
            auto pnum = tree.find_by_number(n);
            if (pnum)
                std::cout << pnum->key << ' ';
            else
                std::cout << "Invalid number\n";
            break;
        }
        case 'n':
            std::cout << tree.less_than(n) << ' ';
            break;
        default:
            std::cerr << "Unknown command\n";
            abort();
            break;
        }
    }

    std::cout << "\n";
    return 0;
}