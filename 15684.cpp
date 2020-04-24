#include <iostream>
#include <cstring>

using namespace std;

int N, M, H;
int answer = 0x3f3f3f3f;
// int MAP[MAX_r][MAX_c]; // MAP[H][N]
bool visited[11][30];

bool Travel()
{
    for (int i = 1; i <= N; i++)
    {
        int c = i;
        int r = 1;

        while (r <= H)
        {
            if (visited[c][r] == true)
            {
                c++;
            }
            else if (visited[c - 1][r] == true)
            {
                c--;
            }
            ++r;
        }

        if (c != i) return false;
    }
    return true;
}

void DFS(int idx, int cnt)
{
    if (cnt > 3) return;
    if (Travel())
    {
        answer = (answer < cnt) ? answer : cnt;
        return;
    }
    for (int i = idx; i <= H; i++)
    {
        for (int j = 1; j < N; j ++)
        {
            if (visited[j][i]) continue;
            if (visited[j - 1][i]) continue;
            if (visited[j + 1][i]) continue;

            visited[j][i] = true;
            DFS(i, cnt + 1);
            visited[j][i] = false;
        }
    }
}

int main()
{
    memset(visited, 0, sizeof(visited));
    cin >> N >> M >> H;
    for (int i = 0; i < M; i++)
    {
        int t1, t2;
        cin >> t1 >> t2;
        visited[t2][t1] = true;
    }

    DFS(1, 0);

    if (answer > 3) answer = -1;
    
    cout << answer << "\n";
    return 0;
}