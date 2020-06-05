#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

int N, M, D;
int ans = -0x3f3f3f3f;
int MAP[16][15];
int C_MAP[16][15];
pair<int, int> attack[3];
pair<int, int> archer[3];

void Copy_MAP()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            C_MAP[i][j] = MAP[i][j];
        }
    }
}

void Game()
{
    int kill = 0;
    bool game_end = false;

    while (true)
    {
        // find enemy
        for (int i = 0; i < 3; i++)
        {
            attack[i] = make_pair(16, 16);
            int enemy = 0x3f3f3f3f;
            for (int j = N - 1; j >= 0; j--)
            {
                for (int k = M - 1; k >= 0; k--)
                {
                    if (C_MAP[j][k] == 1)
                    {
                        int dist = abs(archer[i].first - j) + abs(archer[i].second - k);
                        if (dist > D) continue;

                        if (enemy == dist)
                        {
                            if (attack[i].second >= k)
                            {
                                enemy = dist;
                                attack[i] = make_pair(j, k);
                            }
                        }
                        else if (enemy > dist)
                        { 
                            enemy = dist;
                            attack[i] = make_pair(j, k);
                        }
                    }
                }
            }
        }

        if (attack[0] == attack[1])
        {
            if (attack[1] == attack[2])
            {
                if (attack[0].first != 16)
                {
                    C_MAP[attack[0].first][attack[0].second] = 0;
                    kill++;
                }
            }
            else
            {
                if (attack[0].first != 16)
                {
                    C_MAP[attack[0].first][attack[0].second] = 0;
                    kill++;
                }

                if (attack[2].first != 16)
                {
                    C_MAP[attack[2].first][attack[2].second] = 0;
                    kill++;
                }
            }
        }
        else
        {
            if (attack[0] == attack[2])
            {
                if (attack[0].first != 16)
                {
                    C_MAP[attack[0].first][attack[0].second] = 0;
                    kill++;
                }
                if (attack[1].first != 16)
                {
                    C_MAP[attack[1].first][attack[1].second] = 0;
                    kill++;
                }
            }
            else if (attack[1] == attack[2])
            {
                if (attack[0].first != 16)
                {
                    C_MAP[attack[0].first][attack[0].second] = 0;
                    kill++;
                }
                if (attack[1].first != 16)
                {
                    C_MAP[attack[1].first][attack[1].second] = 0;
                    kill++;
                }
            }
            else
            {
                if (attack[0].first != 16)
                {
                    C_MAP[attack[0].first][attack[0].second] = 0;
                    kill++;
                }
                if (attack[1].first != 16)
                {
                    C_MAP[attack[1].first][attack[1].second] = 0;
                    kill++;
                }
                if (attack[2].first != 16)
                {
                    C_MAP[attack[2].first][attack[2].second] = 0;
                    kill++;
                }
            }
        }

        game_end = true;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (C_MAP[i][j] == 1)
                {
                    game_end = false;
                    break;
                }
            }
            if (!game_end) break;
        }
        
        if (game_end) break;
        
        // move enemy
        for (int i = N - 1; i > 0 ; --i)
        {
            for (int j = 0; j < M; j++)
            {
                C_MAP[i][j] = C_MAP[i - 1][j];
            }
        }
        for (int i = 0; i < M; i++)
        {
            C_MAP[0][i] = 0;
        }
    }

    ans = (ans > kill) ? ans : kill;
}

int main()
{
    memset(MAP, 0, sizeof(MAP));

    cin >> N >> M >> D;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
        }
    }

    for (int i = 0; i < M - 2; i++)
    {
        for (int j = i + 1; j < M - 1; j++)
        {
            for (int k = j + 1; k < M; k++)
            {
                archer[0] = make_pair(N, i);
                archer[1] = make_pair(N, j);
                archer[2] = make_pair(N, k);
                Copy_MAP();           
                Game();
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}