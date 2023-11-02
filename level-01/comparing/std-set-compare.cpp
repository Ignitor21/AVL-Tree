#include <iostream>
#include <ctime>
#include <set>
#include <iterator>

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
            int volatile ans = std::distance(s.lower_bound(lb), s.upper_bound(ub));
            break;
        }
        default:
            std::cerr << "Unknown command\n";
            abort();
            break;
        }
    }

    clock_t fin = clock();
    printf("Time of std::set work: %lg s\n", (static_cast<double>(fin - start))/CLOCKS_PER_SEC);
    return 0;
}