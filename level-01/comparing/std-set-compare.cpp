#include <iostream>
#include <ctime>
#include <set>

int main()
{
    std::set<int> s{};
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
            s.insert(n);
            break;
        }
        case 'q':
        {
            int lb{}, ub{};
            std::cin >> lb >> ub;
            if (lb >= ub)
                break;
            volatile int ans = std::distance(s.lower_bound(lb), s.upper_bound(ub));
            break;
        }
        default:
            std::cerr << "Unknown command\n";
            abort();
            break;
        }
    }

    clock_t fin = clock();
    std::cout << "Time of std::set work: " << (static_cast<double>(fin - start))/CLOCKS_PER_SEC << "s\n";
    return 0;
}