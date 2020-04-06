#include <iostream>
#include <queue>
#include <vector>

const int MAX = 50;
const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int R, C;
char MAP[MAX][MAX];
bool visit[MAX][MAX];
std::pair<int, int> S, D;
std::vector<std::pair<int, int>> water;
std::queue<std::pair<std::pair<int, int>, int>> Q;

void Water_Move(std::vector<std::vector<char>>& m_map, int m_cnt)
{
    std::vector<std::pair<int, int>> m_water = water;
    int num = m_water.size();
    for (int i = 0; i < m_cnt; i++)
    {
        for (int j = 0; j < num; ++j)
        {
            int r = m_water[j].first;
            int c = m_water[j].second;

            for (int k = 0; k < 4; ++k)
            {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < R && nc >= 0 && nc < C)
                    if (m_map[nr][nc] == '.')
                    {
                        m_map[nr][nc] = '*';
                        m_water.push_back({nr, nc});
                    }
            }
        }
        num = m_water.size();
    }
}

int main()
{
    // input
    std::cin >> R >> C;
    for (int i = 0; i < R; i++)
    {
        std::string str;
        std::cin >> str;
        for (int j = 0; j < C; j++)
        {
            MAP[i][j] = str[j];
            if (MAP[i][j] == 'D')
            {
                D = {i, j};
            }
            else if (MAP[i][j] == 'S')
            {
                S = {i, j};
            }
            else if (MAP[i][j] == '*')
            {
                water.push_back({i, j});
            }
        }
    }

    visit[S.first][S.second] = true;
    Q.push({S, 0});

    while (!Q.empty())
    {
        int r = Q.front().first.first;
        int c = Q.front().first.second;
        int cnt = Q.front().second;
        Q.pop();

        std::vector<std::vector<char>> tmp_map;
        for (int i = 0; i < R; i++)
        {
            std::vector<char> tmp;
            for (int j = 0; j < C; j++)
            {
                tmp.push_back(MAP[i][j]);
            }
            tmp_map.push_back(tmp);
        }

        Water_Move(tmp_map, cnt);

        if (tmp_map[r][c] == '*') continue;

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C)
            {
                if (MAP[nr][nc] == 'D')
                {
                    std::cout << cnt + 1 << "\n";
                    return 0;
                }
                
                if (MAP[nr][nc] == '.' && !visit[nr][nc])
                {
                    visit[nr][nc] = true;
                    Q.push({{nr, nc}, cnt + 1});
                }
            }
        }
    }
    
    
    std::cout << "KAKTUS\n";
    return 0;
}