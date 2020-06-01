#include <iostream>
#include <deque>
#include <cstring>

using namespace std;

int N;
int ans = -0x3f3f3f3f;
int bat_ord[9];
bool used[9];
int act[50][9]; // c : heater number r : each inning

void Play_Game()
{
    deque<int> base;
    int out_count = 0;
    int bat_num = 0; // current bat number; bat_num = (bat_num + 1) % 9
    int score = 0;

    for (int i = 0; i < N; i++)
    {
        base.clear();
        out_count = 0;

        while (true)
        {
            if (out_count == 3) break;

            switch (act[i][bat_ord[bat_num]])
            {
            case 0:
                out_count++;
                break;
            case 1:
                base.push_back(bat_ord[bat_num]);
                break;
            case 2:
                base.push_back(bat_ord[bat_num]);
                base.push_back(-1); // empty base
                break;
            case 3:
                base.push_back(bat_ord[bat_num]);
                base.push_back(-1);
                base.push_back(-1);
                break;
            case 4:
                base.push_back(bat_ord[bat_num]);
                base.push_back(-1);
                base.push_back(-1);
                base.push_back(-1);
                break;
            }

            while (base.size() > 3)
            {
                if (base.front() == -1)
                {
                    base.pop_front();
                }
                else
                {
                    base.pop_front();
                    score++;
                }
            }

            bat_num = (bat_num + 1) % 9;
        }
    }

    ans = (ans > score) ? ans : score;
}

void Make_Order(int cnt)
{
    // play game
    if (cnt == 9)
    {
        Play_Game();
        return;
    }

    if (cnt == 3) cnt++;

    for (int i = 1; i < 9; i++)
    {
        if (used[i]) continue;

        used[i] = true;
        bat_ord[cnt] = i;
        Make_Order(cnt + 1);
        used[i] = false;
    }
}

int main()
{
    memset(used, false, sizeof(used));

    // input
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> act[i][j];
        }
    }

    // initial setting
    bat_ord[3] = 0;
    used[0] = true;

    Make_Order(0);
    
    cout << ans << "\n";
    return 0;
}

