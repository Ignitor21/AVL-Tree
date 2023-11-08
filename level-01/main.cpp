#include <iostream>
#include <vector>
#include <functional>
#include "avl.hpp"

using namespace avl;

int main()
{
    AVLTree<int, std::less<int>> tree{};
    char command{};
    while(std::cin >> command)
    {
        switch (command)
        {
        case 'k':
        {
            int n{};
            std::cin >> n;
            tree.insert(n);
            //tree.TreeDump();
            break;
        }
        case 'q':
        {
            int lb{}, ub{};
            std::cin >> lb >> ub;
            //std::cout << tree.distance(lb, ub) << ' ';
            break;
        }
        default:
            std::cerr << "Unknown command\n";
            abort();
            break;
        }
    }

    for(auto it = tree.begin(), end = tree.end(); it != end; ++it)
        std::cout << *it << ' ';
    std::cout << "\n";
    return 0;
}