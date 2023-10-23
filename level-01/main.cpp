#include <iostream>
#include <vector>
#include "avl.hpp"

using namespace avl;

int main()
{
    AVLTree tree{};
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
            break;
        }
        case 'q':
        {
            int lb{}, ub{};
            std::cin >> lb >> ub;
            std::cout << tree.distance(lb, ub) << ' ';
            break;
        }
        default:
            std::cerr << "Unknown command\n";
            abort();
            break;
        }

        #if DEBUG
            tree.TreeDump();
        #endif
    }

    std::cout << "\n";
    return 0;
}