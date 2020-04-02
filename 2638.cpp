#include <iostream>
#include <queue>

const int MAX = 100;
const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int N, M;
int MAP[MAX][MAX];
int visit[MAX][MAX];
int cheese_count = 0;
int cnt = 0;
std::queue<std::pair<int, int>> Q;

void Melt_Cheese()
{
    std::queue<std::pair<int, int>> NQ = Q;
    while (!Q.empty()) Q.pop();
    while (!NQ.empty())
    {
        int r = NQ.front().first;
        int c = NQ.front().second;
        NQ.pop();

        for (int i = 0; i < 4; ++i)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M)
            {
                if (MAP[nr][nc] == 1)
                {
                    // first check
                    if (visit[nr][nc] == -1)
                    {
                        visit[nr][nc] = 2;
                    }
                    // second check
                    else if (visit[nr][nc] == 2)
                    {
                        cheese_count--;
                        MAP[nr][nc] = 0;
                        Q.push({nr,nc});
                    }
                }
            }
        }
    }
}

// merge inner air(checked as 0) with outer air(checked as 1)
void Merg_Air()
{
    std::queue<std::pair<int, int>> NQ = Q;
    while (!NQ.empty())
    {
        int r = NQ.front().first;
        int c = NQ.front().second;
        NQ.pop();
 
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nc >= 0 && nr < N && nc < M)
            {
                if (visit[nr][nc] == 0)
                {
                    visit[nr][nc] = 1;
                    Q.push({nr, nc});
                    NQ.push({nr, nc});
                }
            }
        }
    }
}

// reset checked cheese to default
void Reset_Cheese()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (MAP[i][j] == 1)
            {
                if (visit[i][j] == 2)
                {
                    visit[i][j] = -1;
                }
            }
        }
    }
}

int main()
{

    // input
    std::cin >> N >> M;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
        {
            std::cin >> MAP[i][j];
            if (MAP[i][j] == 1)
            {
                visit[i][j] = -1;
                cheese_count++;
            }
        }

    // find outside air
    visit[0][0] = 1;
    Q.push({0, 0});

    while (!Q.empty())
    {
        int r = Q.front().first;
        int c = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M)
            {
                if (MAP[nr][nc] == 0 && visit[nr][nc] == 0)
                {
                    visit[nr][nc] = 1;
                    Q.push({nr, nc});
                }
            }
        }
    }

    // find air connected with cheese
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (visit[i][j] == 1)
                for (int k = 0; k < 4; k++)
                {
                    int nr = i + dr[k];
                    int nc = j + dr[k];

                    if (nr >= 0 && nr < N && nc >= 0 && nc < M)
                        if (MAP[nr][nc] == 1)
                        {
                            Q.push({i, j});
                            break;
                        }
                }
    
    while (true)
    {
        if (cheese_count == 0) break;
        Melt_Cheese();
        Merg_Air();
        Reset_Cheese();
        cnt++;
    }
    
    std::cout << cnt << "\n";
    
    return 0;
}
