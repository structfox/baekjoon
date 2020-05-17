#include <iostream>
#include <vector>

using namespace std;

const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {1, -1, 0, 0};

int R, C, T;
int MAP[50][50];
int TMP_MAP[50][50];
pair<int, int> air_cleaner;

void Dust()
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (MAP[i][j])
            {
                if (MAP[i][j] != -1)
                {
                    int tmp = (MAP[i][j] / 5);
                    int cnt = 0;

                    for (int k = 0; k < 4; k++)
                    {
                        int nr = i + dr[k];
                        int nc = j + dc[k];
                        if (nr >= 0 && nr < R && nc >= 0 && nc < C)
                        {
                            if (MAP[nr][nc] != -1)
                            {
                                TMP_MAP[nr][nc] += tmp;
                                cnt++;
                            }
                        }
                    }

                    MAP[i][j] -= (tmp * cnt);
                }
            }
        }
    }

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (TMP_MAP[i][j])
            {
                MAP[i][j] += TMP_MAP[i][j];
                TMP_MAP[i][j] = 0;
            }
        }
    }
}

void Clean()
{
    // upside
    for (int i = air_cleaner.first - 1; i > 0; --i)
    {
        MAP[i][0] = MAP[i - 1][0];
    }
    for (int i = 0; i < C - 1; ++i)
    {
        MAP[0][i] = MAP[0][i + 1];
    }
    for (int i = 1; i <= air_cleaner.first; i++)
    {
        MAP[i - 1][C - 1] = MAP[i][C - 1];
    }
    for (int i = C - 1; i > 1; --i)
    {
        MAP[air_cleaner.first][i] = MAP[air_cleaner.first][i - 1];
    }
    MAP[air_cleaner.first][1] = 0;

    // downside
    for (int i = air_cleaner.second + 1; i < R - 1; ++i)
    {
        MAP[i][0] = MAP[i + 1][0];
    }
    for (int i = 0; i < C - 1; ++i)
    {
        MAP[R - 1][i] = MAP[R - 1][i + 1];
    }
    for (int i = R - 1; i >= air_cleaner.second; --i)
    {
        MAP[i][C - 1] = MAP[i - 1][C - 1];
    }
    for (int i = C - 1; i > 1; --i)
    {
        MAP[air_cleaner.second][i] = MAP[air_cleaner.second][i - 1];
    }
    MAP[air_cleaner.second][1] = 0;
}

int main()
{
    bool up_check = false;
    int dust_sum = 0;

    cin >> R >> C >> T;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == -1)
            {
                if (!up_check)
                {
                    air_cleaner.first = i;
                    up_check = true;
                }
                else
                {
                    air_cleaner.second = i;
                }
            }
            TMP_MAP[i][j] = 0;
        }
    }

    for (int i = 0; i < T; i++)
    {
        Dust();
        Clean();
    }
    
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (MAP[i][j] != 0 && MAP[i][j] != -1)
            {
                dust_sum += MAP[i][j];
            }
        }
    }
    
    cout << dust_sum << "\n";
    
    return 0;
}