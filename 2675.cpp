#include <iostream>

int main()
{
    int num;
    std::cin >> num;

    for (int i = 0; i < num; i++)
    {
        int tmp;
        std::string str;
        std::cin >> tmp >> str;
        for (int j = 0; j < str.length(); j++)
        {
            for (int k = 0; k < tmp; k++)
            {
                std::cout << str[j];
            }
        }
        std::cout << "\n";
    }

    return 0;
}