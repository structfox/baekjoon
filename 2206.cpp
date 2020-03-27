#include <iostream>
#include <queue>

const int MAX = 1001;
// East, West, South, North
int dr[4] = {0, 0, 1, -1};
int dc[4] = {1, -1, 0, 0};

int MAP[MAX][MAX];
int N, M;

bool visited[MAX][MAX][2]; // {not breaked, breaked}
bool breaked = false;
int cnt = 1;
std::pair<int, int> rc = {1, 1};
//{{r, c}, {cnt, breaked}}
std::queue<std::pair<std::pair<int, int>, std::pair<int, bool>>> q;

int main()
{
    // input
    std::cin >> N >> M;
    for (int i = 1; i <= N; ++i)
    {
        std::string tmp;
        std::cin >> tmp;
        for (int j = 1; j <= M; ++j)
            MAP[i][j] = tmp[j - 1] - '0';
    }
    
    visited[1][1][0] = true;
    q.push({rc, {cnt, breaked}});

    while (!q.empty())
    {
        rc = q.front().first;
        cnt = q.front().second.first;
        breaked = q.front().second.second;
        q.pop();

        if (rc.first == N && rc.second == M)
        {
            std::cout << cnt << "\n";
            return 0;
        }

        for (int i = 0; i < 4; i++)
        {
            int nr, nc;
            nr = rc.first + dr[i];
            nc = rc.second + dc[i];
            if (nr < 1 || nc < 1 || nr > N || nc > M) continue;

            if (!breaked)
            {
                if (MAP[nr][nc] == 0)
                {
                    if (!visited[nr][nc][0])
                    {
                        visited[nr][nc][0] = true;
                        q.push({{nr, nc}, {cnt + 1, false}});
                    }
                }
                else
                {
                    if (!visited[nr][nc][1])
                    {
                        visited[nr][nc][1] = true;
                        q.push({{nr, nc}, {cnt + 1, true}});
                    }
                }
            }
            else
            {
                if (MAP[nr][nc] == 0)
                {
                    if (!visited[nr][nc][1])
                    {
                        visited[nr][nc][1] = true;
                        q.push({{nr, nc}, {cnt + 1, true}});
                    }
                }
            }
        }
        
    }
    

    std::cout << -1 << "\n";
    return 0;
}