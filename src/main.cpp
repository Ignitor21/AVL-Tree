#include <iostream>
#include <vector>
#include "avl.hpp"

using namespace avl;

int main()
{
    AVLTree tree{};
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
            std::cout << tree.find_by_number(n)->key << ' ';
            break;
        case 'n':
            std::cout << tree.distance(n) << ' ';
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