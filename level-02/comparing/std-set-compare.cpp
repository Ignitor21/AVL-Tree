#include <iostream>
#include <ctime>
#include <set>
#include <iterator>

int main()
{
    std::set<int> s{};
    int n{};
    char command{};
    clock_t start = clock();

    while(std::cin >> command >> n)
    {
        switch (command)
        {
        case 'k':
            s.insert(n);
            break;
        case 'm':
        {
            if (n <= 0)
                return 1;
            if (n > s.size())
                volatile auto iter = s.rbegin();
            volatile auto it = std::next(s.begin(), n - 1);
            break;
        }
        case 'n':
        {
            volatile int ans = std::distance(s.begin(), s.lower_bound(n));
            break;
        }
        default:
            std::cerr << "Unknown command\n";
            return -1;
        }
    }


    clock_t fin = clock();
    std::cout << "Time of std::set work: " << (static_cast<double>(fin - start))/CLOCKS_PER_SEC << "s\n";
    return 0;
}