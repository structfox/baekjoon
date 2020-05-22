#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int N;
int ans = 0x3f3f3f3f;
int S[20][20];
bool man[20];

void Make_Team(int num, int cnt)
{
    if (num == (N / 2))
    {
        int diff;
        int team1 = 0, team2 = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (man[i])
                {
                    if (man[j])
                    {
                        team1 += S[i][j];
                    }
                }
                else
                {
                    if (!man[j])
                    {
                        team2 += S[i][j];
                    }
                }
            }
        }

        diff = abs(team1 - team2);
        if (diff < ans)
        {
            ans = diff;
        }

        return;
    }

    for (int i = cnt; i <= (N / 2) + num; i++)
    {
        man[i] = true;
        Make_Team(num + 1, i + 1);
        man[i] = false;
    }
}

int main()
{
    memset(man,false, sizeof(man));

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> S[i][j];
        }
    }

    Make_Team(0, 0);

    cout << ans << "\n";
    
    return 0;
}