#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int N, L, R;
int cnt = 0;
bool visited[50][50];
int MAP[50][50];
vector<vector<pair<int, int> > > Union;
vector<pair<int, int> > v;

void DFS(int r, int c)
{
    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nc >= 0 && nr < N && nc < N)
        {
            if (visited[nr][nc]) continue;

            int tmp = abs(MAP[nr][nc] - MAP[r][c]);

            if (tmp >= L && tmp <= R)
            {
                v.push_back(make_pair(nr, nc));
                visited[nr][nc] = true;
                DFS(nr, nc);
            }
        }
    }
}

void Population_Move()
{
    memset(visited, false, sizeof(visited));
    Union.clear();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (visited[i][j]) continue;

            v.clear();

            visited[i][j] = true;
            DFS(i, j);

            if (!v.empty())
            {
                v.push_back(make_pair(i, j));
                Union.push_back(v);
            }
        }
    }

    for (int i = 0; i < Union.size(); i++)
    {
        int sum = 0;
        for (int j = 0; j < Union[i].size(); j++)
        {
            sum += MAP[Union[i][j].first][Union[i][j].second];
        }

        for (int j = 0; j < Union[i].size(); j++)
        {
            MAP[Union[i][j].first][Union[i][j].second] = static_cast<int>(sum / Union[i].size());
        }
    }

    if (!Union.empty())
    {
        ++cnt;
        Population_Move();
    }
}

int main()
{
    cin >> N >> L >> R;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            visited[i][j] = false;
        }
    }

    Population_Move();

    cout << cnt << "\n";

    return 0;
}