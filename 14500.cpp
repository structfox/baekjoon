#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 500;
const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int N, M;
int answer = -0x3f3f3f3f;
int MAP[MAX][MAX];
bool visit[MAX][MAX];

void DFS(int r, int c, int cnt, int sum)
{
    visit[r][c] = true;

    if (cnt == 3)
    {
        if (sum > answer)
        {
            answer = sum;
        }
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
        if (visit[nr][nc] == true) continue;

        DFS(nr, nc, cnt + 1, sum + MAP[nr][nc]);
        visit[nr][nc] = false;
    }
}

void Shape1(int x, int y)
{
    int sum = 0;
    sum = MAP[x][y] + MAP[x][y + 1] + MAP[x][y + 2] + MAP[x - 1][y + 1];
    if (sum > answer) answer = sum;
}
 
void Shape2(int x, int y)
{
    int sum = 0;
    sum = MAP[x][y] + MAP[x][y + 1] + MAP[x][y + 2] + MAP[x + 1][y + 1];
    if (sum > answer) answer = sum;
}
 
void Shape3(int x, int y)
{
    int sum = 0;
    sum = MAP[x][y] + MAP[x + 1][y] + MAP[x + 2][y] + MAP[x + 1][y + 1];
    if (sum > answer) answer = sum;
}
 
void Shape4(int x, int y)
{
    int sum = 0;
    sum = MAP[x][y] + MAP[x - 1][y + 1] + MAP[x][y + 1] + MAP[x + 1][y + 1];
    if (sum > answer) answer = sum;
}

int main()
{
    // input
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            memset(visit, false, sizeof(visit));
            DFS(i, j, 0, MAP[i][j]);
            if (i - 1 >= 0 && j + 2 < M) Shape1(i, j);
            if (j + 2 < M && i + 1 < N) Shape2(i, j);
            if (i + 2 < N && j + 1 < M) Shape3(i, j);
            if (i + 1 < N && i - 1 >= 0 && j + 1 < M) Shape4(i, j);
        }
    }
    
    cout << answer << "\n";
    
    return 0;
}