#include <iostream>
#include <vector>
#include <functional>
#include <ctime>
#include "avl.hpp"

using namespace avl;

int main()
{
    AVLTree<int, std::less<int>> tree{};
    int n{};
    char command{};
    clock_t start = clock();

    while(std::cin >> command >> n)
    {
        switch (command)
        {
        case 'k':
            tree.insert(n);
            break;
        case 'm':
        {
            try
            {
                volatile auto it = tree.find_by_number(n);
            }

            catch(const std::range_error& e)
            {
                std::cout << e.what();
                return 1;
            }
            break;
        }
        case 'n':
        {
            volatile int ans = tree.less_than(n);
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