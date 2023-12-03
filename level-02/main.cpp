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
            try
            {
                auto it = tree.find_by_number(n);
                if (it != tree.end())
                    std::cout << *it << ' ';
            }

            catch(const std::range_error& e)
            {
                std::cout << e.what();
                return 1;
            }
            break;
        }
        case 'n':
            std::cout << tree.less_than(n) << ' ';
            break;
        default:
            std::cerr << "Unknown command\n";
            return -1;
        }
    }

    std::cout << "\n";
    return 0;
}