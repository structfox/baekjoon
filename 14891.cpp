#include <iostream>
#include <cstring>

using namespace std;

int K;
int gear[4][8];
bool visited[4];

void rotate_clock(int num)
{
    int tmp = gear[num][7];
    for (int i = 7; i > 0; i--)
    {
        gear[num][i] = gear[num][i - 1];
    }
    gear[num][0] = tmp;
}

void rotate_anti_clock(int num)
{
    int tmp = gear[num][0];
    for (int i = 0; i < 7; i++)
    {
        gear[num][i] = gear[num][i + 1];
    }
    gear[num][7] = tmp;
}

void is_rotate(int num, int dir)
{
    visited[num] = true;

    int n_num = num + 1;
    if (n_num < 4)
    {
        if (!visited[n_num])
        {
            if (gear[num][2] != gear[n_num][6])
            {
                is_rotate(n_num, (0 - dir));
            }
        }
    }

    n_num = num - 1;
    if (n_num >= 0)
    {
        if (!visited[n_num])
        {
            if (gear[num][6] != gear[n_num][2])
            {
                is_rotate(n_num, (0 - dir));
            }
        }
    }
    

    if (dir == 1)
    {
        rotate_clock(num);
    }
    else
    {
        rotate_anti_clock(num);
    }
}

int main()
{
    int ans = 0;
    for (int i = 0; i < 4; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < 8; j++)
        {
            gear[i][j] = s[j] - '0';
        }
        
    }

    cin >> K;
    for (int i = 0; i < K; i++)
    {
        memset(visited, false, sizeof(visited));
        int gear_num, dir;
        cin >> gear_num >> dir;
        is_rotate(gear_num - 1, dir);
    }
    
    if (gear[0][0])
    {
        ans += 1;
    }
    if (gear[1][0])
    {
        ans += 2;
    }
    if (gear[2][0])
    {
        ans += 4;
    }
    if (gear[3][0])
    {
        ans += 8;
    }

    cout << ans << "\n";
    
    return 0;
}