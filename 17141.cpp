#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int N, M;
int safe_area = 0;
int ans = 0x3f3f3f3f;
bool visited[50][50];
int MAP[50][50];
int C_MAP[50][50];
bool virus_enabled[10];
vector<pair<int, int> > virus_location;
vector<pair<int, int> > virus_selected;

void Spread_Virus()
{
    int cnt = 0;
    int safe_tmp = safe_area;
    queue<pair<int, int> > Q;

    for (int i = 0; i < virus_selected.size(); i++)
    {
        int r = virus_selected[i].first;
        int c = virus_selected[i].second;
        Q.push(make_pair(r, c));
        visited[r][c] = true;
        safe_tmp--;
    }
    
    // spread virus
    while (!Q.empty())
    {
        int S = Q.size();
        for (int i = 0; i < S; i++)
        {
            int r = Q.front().first;
            int c = Q.front().second;
            Q.pop();

            for (int i = 0; i < 4; i++)
            {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < N && nc >= 0 && nc < N)
                {
                    if (MAP[nr][nc] != 1 && !visited[nr][nc])
                    {
                        visited[nr][nc] = true;
                        Q.push(make_pair(nr, nc));
                        safe_tmp--;
                    }
                }
            }
        }
        if (!Q.empty()) cnt++;
    }
    if (safe_tmp == 0)
    {
        ans = (ans < cnt) ? ans : cnt;
    }
}

void Select_Virus(int cnt, int idx)
{
    if (cnt == M)
    {
        memset(visited, false, sizeof(visited));
        Spread_Virus();
        return;
    }

    for (int i = idx; i < virus_location.size(); i++)
    {
        if (virus_enabled[i]) continue;

        virus_enabled[i] = true;
        virus_selected.push_back(virus_location[i]);
        Select_Virus(cnt + 1, i);

        virus_selected.pop_back();
        virus_enabled[i] = false;
    }
}

int main()
{
    memset(virus_enabled, false, sizeof(virus_enabled));

    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == 2)
            {
                virus_location.push_back(make_pair(i, j));
                safe_area++;
            }
            else if (MAP[i][j] == 0)
            {
                safe_area++;
            }
        }
    }

    Select_Virus(0, 0);

    if (ans == 0x3f3f3f3f) ans = -1;

    cout << ans << "\n";
    
    return 0;
}