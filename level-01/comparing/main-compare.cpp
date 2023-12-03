#include <iostream>
#include <vector>
#include <functional>
#include <ctime>
#include "avl.hpp"

using namespace avl;

int main()
{
    AVLTree<int, std::less<int>> tree{};
    char command{};
    clock_t start = clock();

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
            volatile int ans = tree.distance(lb, ub);
            break;
        }
        default:
            std::cerr << "Unknown command\n";
            return -1;
        }
    }

    clock_t fin = clock();
    std::cout << "Time of AVL tree work: " << (static_cast<double>(fin - start))/CLOCKS_PER_SEC << "s\n";
    return 0;
}