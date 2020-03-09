#include <iostream>

int main()
{
    int N, cnt;

    std::cin >> N;

    if (N == 4 || N == 7)
        std::cout << -1 << "\n";
    else
    {
        cnt = N / 5;
        switch (N % 5)
        {
            case 2:
            case 4:
                cnt += 2;
                break;
            case 1:
            case 3:
                cnt += 1;
                break;
            default:
                break;
        }
        std::cout << cnt << "\n";
    }
    
    return 0;
}