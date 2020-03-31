#include <iostream>

int main()
{
    int cnt = 0;
    int seq = 0;
    int num;

    std::cin >> num;

    for (int i = 0; i < num; ++i)
    {
        std::string str;
        std::cin >> str;
        for (int j = 0; j < str.length(); j++)
        {
            if (str[j] == 'O')
            {
                seq++;
                cnt += seq;
            }
            else if (str[j] == 'X')
            {
                seq = 0;
            }
        }
        std::cout << cnt << "\n";
        cnt = 0;
        seq = 0;
    }

    return 0;
}