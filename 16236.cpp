#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

struct Shark
{
    int r;
    int c;
    int size;
    int eat_count;
    int move_count;
};

struct Fish
{
    int r;
    int c;
    int dist;
};

int N;
int MAP[20][20];
bool visit[20][20];

Shark S;
vector<Fish> V;

void BFS(int r, int c)
{
    queue<pair<pair<int, int>, int> > Q;
    Q.push(make_pair(make_pair(r, c), 0));
    visit[r][c] = true;

    while (!Q.empty())
    {
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int dist = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; ++i)
        {
            int nr = x + dr[i];
            int nc = y + dc[i];

            if (nr >= 0 && nc >= 0 && nr < N && nc < N)
            {
                if (!visit[nr][nc])
                {
                    if (MAP[nr][nc] == 0)
                    {
                        visit[nr][nc] = true;
                        Q.push(make_pair(make_pair(nr, nc), dist + 1));
                    }
                    else if (MAP[nr][nc] < S.size)
                    {
                        Fish tmp;
                        tmp.r = nr;
                        tmp.c = nc;
                        tmp.dist = dist + 1;

                        V.push_back(tmp);
                        visit[nr][nc] = true;
                        Q.push(make_pair(make_pair(nr, nc), dist + 1));
                    }
                    else if (MAP[nr][nc] == S.size)
                    {
                        visit[nr][nc] = true;
                        Q.push(make_pair(make_pair(nr, nc), dist + 1));
                    }
                }
            }
        }
    }
}

bool Sort_Fish(Fish A, Fish B)
{
    if (A.dist <= B.dist)
    {
        if (A.dist == B.dist)
        {
            if (A.r <= B.r)
            {
                if (A.r == B.r)
                {
                    if (A.c < B.c)
                    {
                        return true;
                    }
                    return false;
                }
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == 9)
            {
                S.r = i;
                S.c = j;
                S.size = 2;
                S.eat_count = 0;
                S.move_count = 0;
            }
        }
    }

    while (true)
    {
        V.clear();
        memset(visit, false, sizeof(visit));

        BFS(S.r, S.c);
        if (V.size() == 0)
        {
            cout << S.move_count << "\n";
            break;
        }
        else if (V.size() == 1)
        {
            MAP[V[0].r][V[0].c] = 9;
            MAP[S.r][S.c] = 0;
            S.r = V[0].r;
            S.c = V[0].c;
            S.eat_count++;
            S.move_count += V[0].dist;

            if (S.eat_count == S.size)
            {
                S.eat_count = 0;
                S.size++;
            }
        }
        else
        {
            sort(V.begin(), V.end(), Sort_Fish);
            MAP[V[0].r][V[0].c] = 9;
            MAP[S.r][S.c] = 0;
            S.r = V[0].r;
            S.c = V[0].c;
            S.eat_count++;
            S.move_count += V[0].dist;

            if (S.eat_count == S.size)
            {
                S.eat_count = 0;
                S.size++;
            }
        }
    }

    return 0;
}