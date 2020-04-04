#include <iostream>
#include <queue>
#include <vector>

const int MAX = 100;
const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int N, M;
int MAP[MAX][MAX];
int visit[MAX][MAX];
int cheese_count = 0;
int cnt = 0;
std::queue<std::pair<int, int>> Q;
std::vector<std::pair<int,int>> Cheese; // Save Cheeses which connected with air more than twice
std::vector<std::pair<std::pair<int,int>, bool>> V; // Cheese location, whether it's melted

void Find_Cheese_List()
{
    /* 실질적으로 녹는 치즈들만 저장하는 과정. */
    Cheese.clear(); // empty previous cheese location
    for (int i = 0; i < V.size(); i++)
    {
        if (V[i].second == true) continue; // check cheese melted
 
        int r = V[i].first.first;
        int c = V[i].first.second;
        int Cnt = 0;
 
        for (int j = 0; j < 4; j++)
        {
            int nr = r + dr[j];
            int nc = c + dc[j];
            if (MAP[nr][nc] == 0 && visit[nr][nc] == 1) Cnt++; //connected with outside air count
            // 단순히, MAP[nx][ny] == 0이 아닌, Visit의 값으로 외부공기인지 내부공기인지
            // 체크도 해줘야 한다.
        }
 
        if (Cnt >= 2)
        {
            Cheese.push_back({r, c}); // add to melt candidate cheese
            V[i].second = true;
        }
    }
}

void Melt_Cheese()
{
    for (int i = 0; i < Cheese.size(); i++)
    {
        int r = Cheese[i].first;
        int c = Cheese[i].second;
        MAP[r][c] = 0;
        cheese_count--;
        Q.push({r, c});
    }
    
}

// merge inner air(checked as 0) with outer air(checked as 1)
void Merg_Air()
{
    while (!Q.empty())
    {
        int r = Q.front().first;
        int c = Q.front().second;
        Q.pop();
 
        visit[r][c] = 1;
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (visit[nr][nc] == 0)
            {
                visit[nr][nc] = 1;
                Q.push({nr, nc});
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
                V.push_back({{i, j}, false});
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

    while (true)
    {
        if (cheese_count == 0) break;
        Find_Cheese_List();
        Melt_Cheese();
        Merg_Air();
        cnt++;
    }
    
    std::cout << cnt << "\n";
    
    return 0;
}
