#include <iostream>

int main()
{
    int num[9];
    int cnt, max = -1; 
    for (int i = 0; i < 9; ++i)
        std::cin >> num[i];

    for (int i = 0; i < 9; ++i)
    {
        if (num[i] > max)
        {
            cnt = i;
            max = num[i];
        }
    }
    std::cout << max << "\n" << cnt + 1 << "\n";

    return 0;
}