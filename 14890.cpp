#include <iostream>
#include <vector>

using namespace std;

int N, L;
int ans = 0;
int MAP[100][100];
vector<int> V;
vector<bool> installed;

void Cross()
{
    int ground = V[0];

    for (int i = 1; i < V.size(); i++)
    {
        if (ground != V[i])
        {
            if (ground + 1 == V[i])
            {
                for (int j = 0; j < L; j++)
                {
                    int tmp = i - j - 1;
                    if (tmp < 0) return;
                    if (V[tmp] != ground) return;
                    if (installed[tmp]) return;
                }
                for (int j = 0; j < L; j++)
                {
                    installed[i - j - 1] = true;
                }
                ground = V[i];
            }
            else if (ground - 1 == V[i])
            {
                for (int j = 0; j < L; j++)
                {
                    int tmp = i + j;
                    if (tmp >= N) return;
                    if (V[tmp] != ground - 1) return;
                    if (installed[tmp]) return;
                }
                for (int j = 0; j < L; j++)
                {
                    installed[i + j] = true;
                }
                ground = V[i];
            }
            else
            {
                return;
            }
        }
    }

    ans++;
}

int main()
{
    cin >> N >> L;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> MAP[i][j];
        }
    }

    for (int i = 0; i < N; i++)
    {
        // row
        V.clear();
        installed = vector<bool>(N, false);
        for (int j = 0; j < N; j++)
        {
            V.push_back(MAP[i][j]);
        }
        Cross();

        // column
        V.clear();
        installed = vector<bool>(N, false);
        for (int j = 0; j < N; j++)
        {
            V.push_back(MAP[j][i]);
        }
        Cross();
    }
    
    cout << ans << "\n";
    return 0;
}