#include <iostream>
#include <vector>

using namespace std;

struct Rot
{
    int r;
    int c;
    int s;
};

int N, M, K;
int ans = 0x3f3f3f3f;
int MAP[50][50];
int C_MAP[50][50];
Rot op[6];
bool used[6];
vector<Rot> od;

void Copy_MAP()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            C_MAP[i][j] = MAP[i][j];
        }
    }
}

void Rotate_MAP(int r, int c, int s)
{
    for (int i = 1; i <= s; i++)
    {
        int tmp = C_MAP[r - i][c - i];
        int idx = i * 2;
        for (int j = 0; j < idx; j++)
        {
            C_MAP[r - i + j][c - i] = C_MAP[r - i + j + 1][c - i];
        }
        for (int j = 0; j < idx; j++)
        {
            C_MAP[r + i][c - i + j] = C_MAP[r + i][c - i + j + 1];
        }
        for (int j = 0; j < idx; j++)
        {
            C_MAP[r + i - j][c + i] = C_MAP[r + i - j - 1][c + i];
        }
        for (int j = 0; j < idx; j++)
        {
            C_MAP[r - i][c + i - j] = C_MAP[r - i][c + i - j - 1];
        }
        C_MAP[r - i][c - i + 1] = tmp;
    }
}

void Order(int cnt)
{
    if (cnt == K)
    {
        int sum = 0x3f3f3f3f;

        Copy_MAP();
        for (int i = 0; i < K; i++)
        {
            Rotate_MAP(od[i].r - 1, od[i].c - 1, od[i].s);
        }

        for (int i = 0; i < N; i++)
        {
            int tmp = 0;
            for (int j = 0; j < M; j++)
            {
                tmp += C_MAP[i][j];
            }
            sum = (sum < tmp) ? sum : tmp;
        }
        
        ans = (ans < sum) ? ans : sum;
        return;
    }

    for (int i = 0; i < K; ++i) 
    {
        if (used[i]) continue;

        used[i] = true;
        od.push_back(op[i]);
        Order(cnt + 1);
        od.pop_back();
        used[i] = false;
    }
}

int main()
{
    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
        }
    }

    for (int i = 0; i < K; i++)
    {
        cin >> op[i].r >> op[i].c >> op[i].s;
        used[i] = false;
    }

    od.clear();
    Order(0);

    cout << ans << "\n";

    return 0;
}