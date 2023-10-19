#include <iostream>
#include <set>

int main()
{
    std::set<int> s{};
    char command{};

    while(std::cin >> command)
    {
        switch (command)
        {
        case 'k':
        {
            int n{};
            std::cin >> n;
            s.insert(n);
            break;
        }
        case 'q':
        {
            int lb{}, ub{};
            std::cin >> lb >> ub;   
            if (lb >= ub)
                std::cout << 0 << ' ';
            else
                std::cout << std::distance(s.lower_bound(lb), s.upper_bound(ub)) << ' ';
            break;
        }
        default:
            std::cerr << "Unknown command\n";
            abort();
            break;
        }
    }

    std::cout << "\n";
    return 0;
}