#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;
    while (a + b)
    {
        std::cout << a + b << "\n";
        std::cin >> a >> b;
    }
    return 0;
}