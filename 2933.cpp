#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int R, C, N;
char MAP[100][100];
bool visited[100][100];
bool cluster[100][100];
vector<int> order;
vector<pair<int, int> > mineral_float;

// find connected minerals
void Find_Ground(int r, int c)
{
    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nc >= 0 && nr < R && nc < C)
        {
            if (!visited[nr][nc] && MAP[nr][nc] == 'x')
            {
                visited[nr][nc] = true;
                Find_Ground(nr, nc);
            }
        }
    }
}

void Find_Float()
{
    // find from bottom
    for (int i = R - 1; i >= 0; --i)
    {
        for (int j = 0; j < C; ++j)
        {
            if (MAP[i][j] == 'x' && !visited[i][j])
            {
                mineral_float.push_back(make_pair(i, j));
                cluster[i][j] = true;
            }
        }
    }
}

int Fall_Count(int r, int c)
{
    int cnt = 0;
    for (int i = r + 1; i < R; ++i)
    {
        if (MAP[i][c] == 'x')
        {
            if (cluster[i][c]) return INF;
            
            else return cnt;
        }
        else cnt++;
    }
    
    return cnt;
}

void ReMAP()
{
    int height = INF;
    for (int i = 0; i < mineral_float.size(); ++i)
    {
        int r = mineral_float[i].first;
        int c = mineral_float[i].second;

        int height_rc = Fall_Count(r, c);

        if (height_rc == INF) continue;
        // find height limit
        height = (height < height_rc) ? height : height_rc;
    }

    // move from bottom
    for (int i = 0; i < mineral_float.size(); i++)
    {
        int r = mineral_float[i].first;
        int c = mineral_float[i].second;

        MAP[r][c] = '.';
        MAP[r + height][c] = 'x';
    }
}

int main()
{
    cin >> R >> C;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> MAP[i][j];
        }
    }

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        order.push_back(a);
    }
    
    for (int i = 0; i < order.size(); i++)
    {
        memset(visited, 0, sizeof(visited));
        memset(cluster, 0, sizeof(cluster));
        mineral_float.clear();

        int height = order[i];

        // throw stick and remove mineral
        if (i % 2 == 0)
        {
            for (int j = 0; j < C; j++)
            {
                if (MAP[R - height][j] == 'x')
                {
                    MAP[R - height][j] = '.';
                    break;
                }
            }
        }
        else
        {
            for (int j = C - 1; j >= 0; j--)
            {
                if (MAP[R - height][j] == 'x')
                {
                    MAP[R - height][j] = '.';
                    break;
                }
            }
        }

        // find float cluster
        for (int j = 0; j < C; j++)
        {
            if (MAP[R - 1][j] == 'x' && !visited[R - 1][j])
            {
                visited[R - 1][j] = true;
                Find_Ground(R - 1, j);
            }
        }
        Find_Float();
        ReMAP();
    }

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cout << MAP[i][j];
        }
        cout << "\n";
    }
    
    return 0;
}