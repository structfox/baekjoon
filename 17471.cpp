#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>

using namespace std;

int N;
int ans = 0x3f3f3f3f;
int Population[10];
bool is_selected[10];
bool visited[10];
int MAP[10][10];

bool is_connected(bool T, vector<int>& V)
{
    memset(visited, false, sizeof(visited));

    int cnt = 0;
    queue<int> Q;

    Q.push(V[0]);
    visited[V[0]] = true;
    cnt++;

    while (!Q.empty())
    {
        int r = Q.front();
        Q.pop();

        for (int i = 0; i < N; i++)
        {
            if (is_selected[i] == T)
            {
                if (!visited[i])
                {
                    if (MAP[r][i] == 1)
                    {
                        visited[i] = true;
                        cnt++;
                        Q.push(i);
                    }
                }
            }
        }
    }

    if (cnt != V.size()) return false;

    return true;
}

bool Check()
{
    vector<int> A, B;
    for (int i = 0; i < N; i++)
    {
        if (is_selected[i]) A.push_back(i);
        else B.push_back(i);
    }

    if (A.empty() || B.empty()) return false;
    if (!is_connected(true, A)) return false;
    if (!is_connected(false, B)) return false;

    return true;
}

void Calc()
{
    int A_pop = 0;
    int B_pop = 0;
    int diff;

    for (int i = 0; i < N; i++)
    {
        if (is_selected[i]) A_pop += Population[i];
        else B_pop += Population[i];
    }
    diff = abs(A_pop - B_pop);

    ans = (ans < diff) ? ans : diff;
}

void DFS(int idx, int cnt)
{
    if (cnt >= 1)
    {
        if (Check())
        {
            Calc();
        }
    }
    
    for (int i = idx; i < N; i++)
    {
        if (is_selected[i]) continue;

        is_selected[i] = true;
        DFS(i, cnt + 1);
        is_selected[i] = false;
    }
}

int main()
{
    memset(MAP, 0, sizeof(MAP));

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> Population[i];
    }

    for (int i = 0; i < N; i++)
    {
        int num;
        cin >> num;
        for (int j = 0; j < num; j++)
        {
            int tmp;
            cin >> tmp;
            --tmp;
            MAP[i][tmp] = 1;
        }
    }
    
    DFS(0, 0);
    
    if (ans == 0x3f3f3f3f) ans = -1;
    cout << ans << "\n";
    
    return 0;
}