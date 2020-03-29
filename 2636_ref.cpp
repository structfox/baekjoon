#include<iostream>
#include<queue>
using namespace std;

const int MAX = 100;
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
 
int N, M;
int MAP[MAX][MAX];
int Visit[MAX][MAX];
int cheese_count = 0;
 
queue<pair<int, int>> NQ;
 
void Melt_Cheese()
{
    queue<pair<int, int>> Q = NQ;
    while (!NQ.empty()) NQ.pop();
    while (!Q.empty())
    {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
 
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < N && ny < M)
            {
                if (MAP[nx][ny] == 1)
                {
                    cheese_count--;
                    MAP[nx][ny] = 0;
                    NQ.push(make_pair(nx, ny));
                }
            }
        }
    }
}
 
void Merge_Air()
{
    queue<pair<int, int>> Q = NQ;
    while (Q.empty() == 0)
    {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
 
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < N && ny < M)
            {
                if (Visit[nx][ny] == 0)
                {
                    Visit[nx][ny] = 1;
                    Q.push(make_pair(nx, ny));
                    NQ.push(make_pair(nx, ny));
                }
            }
        }
    }
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    // input
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == 1)
            {
                Visit[i][j] = -1;    // 입력과 동시에 치즈가 있는 좌표는 -1로 표시
                cheese_count++;
            }
        }
    }
    
    // first air
    queue<pair<int, int>> Q;
    Q.push(make_pair(0, 0));
    Visit[0][0] = 1;
 
    while (Q.empty() == 0)
    {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
 
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
 
            if (nx >= 0 && ny >= 0 && nx < N && ny < M)
            {
                if (MAP[nx][ny] == 0 && Visit[nx][ny] == 0)
                {
                    Visit[nx][ny] = 1;
                    Q.push(make_pair(nx, ny));
                }
            }
        }
    }

    // divide
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (Visit[i][j] == 1)
            {
                for (int k = 0; k < 4; k++)
                {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (nx >= 0 && ny >= 0 && nx < N && ny < M)
                    {
                        if (MAP[nx][ny] == 1)
                        {
                            NQ.push(make_pair(i, j));
                            break;
                        }
                    }
                }
            }
        }
    }

    int cnt = 0;
    int last_size = 0;
 
    while (1)
    {
        if (cheese_count == 0) break;
        
        Melt_Cheese();
        last_size = NQ.size();
 
        Merge_Air();
        cnt++;
    }
    cout << cnt << "\n" << last_size << "\n";
 
    return 0;
}