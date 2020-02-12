#include <iostream>
#include <string>

int main()
{
    for (std::string temp; std::getline(std::cin, temp);)
    {
        std::cout << temp << "\n";
    }
    return 0;
}