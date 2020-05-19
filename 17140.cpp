#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int R, C, K;
int ans = 0, row = 3, col = 3;
vector<pair<int, int> > num; // count, number
int num_cnt[101];
int MAP[101][101];

int main()
{
    cin >> R >> C >> K;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            cin >> MAP[i][j];
        }
    }

    if (MAP[R][C] == K)
    {
        cout << ans << "\n";
        return 0;
    }

    while (1)
    {
        if (MAP[R][C] == K) break;
        if (ans > 100) { ans = -1; break; }
 
        vector<int> Size;
        if (row >= col)    // 정사각형이거나 세로로긴 형태
        {
            for (int i = 1; i <= row; i++)
            {
                vector<pair<int, int>> V;
                memset(num_cnt, 0, sizeof(num_cnt));
                for (int j = 1; j <= col; j++) num_cnt[MAP[i][j]]++;
                for (int j = 1; j < 101; j++)
                {
                    if (num_cnt[j] == 0) continue;
                    V.push_back(make_pair(num_cnt[j], j));
                }
                sort(V.begin(), V.end());
                for (int j = 1; j <= col; j++) MAP[i][j] = 0;
                int Idx = 1;
                for (int j = 0; j < V.size(); j++)
                {
                    MAP[i][Idx++] = V[j].second;
                    MAP[i][Idx++] = V[j].first;
                }
                Idx--;
                Size.push_back(Idx);
            }
            sort(Size.begin(), Size.end());
            col = Size.back();
        }
        else        // 가로로 더 긴꼴
        {
            for (int i = 1; i <= col; i++)
            {
                vector<pair<int, int>> V;
                memset(num_cnt, 0, sizeof(num_cnt));
                for (int j = 1; j <= row; j++) num_cnt[MAP[j][i]]++;
                for (int j = 1; j < 101; j++)
                {
                    if (num_cnt[j] == 0) continue;
                    V.push_back(make_pair(num_cnt[j], j));
                }
                sort(V.begin(), V.end());
                for (int j = 1; j <= row; j++) MAP[j][i] = 0;
                int Idx = 1;
                for (int j = 0; j < V.size(); j++)
                {
                    MAP[Idx++][i] = V[j].second;
                    MAP[Idx++][i] = V[j].first;
                }
                Idx--;
                Size.push_back(Idx);
            }
            sort(Size.begin(), Size.end());
            row = Size.back();
        }
        ans++;
    }
    cout << ans << "\n";
    
    return 0;
}