#include <iostream>
#include <vector>

using namespace std;

const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int N;
int ans = 0x3f3f3f3f;
int MAP[10][10];
int visited[10][10];
vector<pair<int, int> > flower;

void Find_Flower(int cnt, int idx)
{
    if (cnt == 3)
    {
        int sum = 0;
        for (int i = 0; i < flower.size(); i++)
        {
            int r = flower[i].first;
            int c = flower[i].second;

            sum += MAP[r][c];
            for (int j = 0; j < 4; j++)
            {
                int nr = r + dr[j];
                int nc = c + dc[j];
                sum += MAP[nr][nc];
            }
        }
        
        ans = (ans < sum) ? ans : sum;
        return;
    }

    for (int i = idx; i < N - 1; i++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            if (visited[i][j]) continue;

            if (visited[i][j - 1] || visited[i][j + 1] || visited[i - 1][j] || visited[i + 1][j]) continue;

            visited[i][j] = true;
            for (int k = 0; k < 4; k++)
            {
                int r = i + dr[k];
                int c = j + dc[k];
                visited[r][c] = true;
            }
            flower.push_back(make_pair(i, j));
            Find_Flower(cnt + 1, i);

            flower.pop_back();
            for (int k = 0; k < 4; k++)
            {
                int r = i + dr[k];
                int c = j + dc[k];
                visited[r][c] = false;
            }
            visited[i][j] = false;
        }
    }
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
        }
    }

    Find_Flower(0, 1);

    cout << ans << "\n";
    
    return 0;
}