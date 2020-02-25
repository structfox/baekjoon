#include <iostream>
#include <vector>

int main()
{
    int L, N;
    int x = 0, y = 0;
    int dir = 0;
    const int DIR[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    char pos = 'A'; // set Left or Right

    std::cin >> L >> N;
    std::vector<std::vector<int>> map(2 * L + 1, std::vector<int>(2 * L + 1, 0));
    map[L][L] = 1; // (0, 0) start position

    int cnt = 0;
    int cng = INT_MAX;

    for(;;)
    {
        ++cnt;

        if (cnt == cng)
        {
            if (pos == 'L')
                dir = (dir + 1) % 4;
            else if (pos == 'R')
            {
                if (dir == 0)
                    dir = 3;
                else
                    --dir;
            }
        }

        x += DIR[dir][0];
        y += DIR[dir][1];

        if ( (x > L) || (x < -L) // x is not in range
        || (y > L) || (y < -L) // y is not in range
        || map[y + L][x + L] == 1 ) // already visited
        {
            std::cout << cnt;
            break;
        }

        map[y + L][x + L] = 1;

        if (cnt == cng || cnt == 1)
            if ( N > 0)
            {
                --N;
                int temp;
                std::cin >> temp >> pos;
                cng = cnt + temp;
            }
    }

    return 0;
}