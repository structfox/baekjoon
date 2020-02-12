#include <iostream>
#include <string>

int main()
{
    std::string temp;
    std::cin >> temp;

    for (int i = 0; i < temp.length();)
    {
        for (int j = 0; (j < 10) && (i < temp.length()); ++j)
        {
            std::cout << temp.at(i);
            ++i;
        }
        std::cout << "\n";
    }
    return 0;
}