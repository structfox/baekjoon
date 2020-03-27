#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;
    if (a > b)
        std::cout << ">" << "\n";
    else if (a < b)
        std::cout << "<" << "\n";
    else
    {
        std::cout << "==" << "\n";
    }
    
    return 0;
}