#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX = 8;
const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int N, M;
int answer = -0x3f3f3f3f;
int MAP[MAX][MAX];
int c_MAP[MAX][MAX];
vector< pair<int, int> > virus;
vector< pair<int, int> > safe;

void Copy_Map()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            c_MAP[i][j] = MAP[i][j];
}

void Spread_Virus()
{
    queue< pair<int, int > > v;
    for (int i = 0; i < virus.size(); i++)
    {
        v.push(virus[i]);
    }

    while (!v.empty())
    {
        int r = v.front().first;
        int c = v.front().second;
        v.pop();

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >=0 && nr < N && nc >= 0 && nc < M)
            {
                if (c_MAP[nr][nc] == 0)
                {
                    c_MAP[nr][nc] = 2;
                    v.push(make_pair(nr, nc));
                }
            }
        }
    }
}

void Count_Safe()
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (c_MAP[i][j] == 0)
            {
                cnt++;
            }
        }
    }
    answer = (cnt > answer) ? cnt : answer;
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
            if (MAP[i][j] == 2)
            {
                virus.push_back(make_pair(i, j));
            }
            else if (MAP[i][j] == 0)
            {
                safe.push_back(make_pair(i, j));
            }
        }
    }

    for (int i = 0; i < safe.size() - 2; i++)
    {
        for (int j = i + 1; j < safe.size() - 1; j++)
        {
            for (int k = j + 1; k < safe.size(); k++)
            {
                Copy_Map();
                c_MAP[safe[i].first][safe[i].second] = 1;
                c_MAP[safe[j].first][safe[j].second] = 1;
                c_MAP[safe[k].first][safe[k].second] = 1;

                Spread_Virus();

                Count_Safe();
            }
        }
    }
    
    cout << answer << "\n";
    
    return 0;
}