#include <iostream>
#include <queue>

const int MAX = 100;
const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int N, M;
int MAP[MAX][MAX];
int visit[MAX][MAX];
int cheese_count = 0;
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
 
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nc >= 0 && nr < N && nc < M)
            {
                if (MAP[nr][nc] == 1)
                {
                    cheese_count--;
                    MAP[nr][nc] = 0;
                    Q.push({nr, nc});
                }
            }
        }
    }
}
 
// merge inner air, outer air
void Merge_Air()
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

int main()
{
    int cnt = 0;
    int last_size = 0;

    std::cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            std::cin >> MAP[i][j];
            if (MAP[i][j] == 1)
            {
                visit[i][j] = -1;
                cheese_count++;
            }
        }
        
    // check for outside air
    visit[0][0] = 1;
    Q.push({0,0});

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
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (visit[i][j] == 1)
            {
                for (int k = 0; k < 4; k++)
                {
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if (nr >= 0 && nc >=0 && nr < N && nc < M)
                    {
                        if (MAP[nr][nc] == 1)
                        {
                            Q.push({nr, nc});
                            break;
                        }
                    }
                }
            }
            
    while (true)
    {
        if (cheese_count == 0) break;
        
        Melt_Cheese();
        last_size = Q.size();
 
        Merge_Air();
        cnt++;
    }

    std::cout << cnt << "\n" << last_size << "\n";

    return 0;
}