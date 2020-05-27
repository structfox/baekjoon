#include <iostream>

using namespace std;

int N;
int ans = 0;
int MAP[16][16];

struct Pipe
{
    int dir; // horizontal : 0, vertical : 1, diagonal : 2
    pair<int, int> tail;
    pair<int, int> head;
};

void Move_Horizontal(Pipe& p)
{
    switch (p.dir)
    {
    case 0:
        p.tail.second++;
        p.head.second++;
        break;
    case 2:
        p.tail.first++;
        p.tail.second++;
        p.head.second++;
        break;
    }
    p.dir = 0;
}

void Move_Vertical(Pipe& p)
{
    switch (p.dir)
    {
    case 1:
        p.tail.first++;
        p.head.first++;
        break;
    case 2:
        p.tail.first++;
        p.tail.second++;
        p.head.first++;
        break;
    }
    p.dir = 1;
}

void Move_Diagonal(Pipe& p)
{
    switch (p.dir)
    {
    case 0:
        p.tail.second++;
        p.head.first++;
        p.head.second++;
        break;
    case 1:
        p.tail.first++;
        p.head.first++;
        p.head.second++;
        break;
    case 2:
        p.tail.first++;
        p.tail.second++;
        p.head.first++;
        p.head.second++;
        break;
    }
    p.dir = 2;
}

void Pipe_Move(Pipe& p)
{
    if (p.head.first >= N || p.head.second >= N) return;
    if (p.dir == 0 && MAP[p.head.first][p.head.second] == 1) return;
    if (p.dir == 1 && MAP[p.head.first][p.head.second] == 1) return;
    if (p.dir == 2)
    {
        if (MAP[p.head.first][p.head.second] == 1
            || MAP[p.head.first - 1][p.head.second] == 1
            || MAP[p.head.first][p.head.second - 1] == 1) return;
    }

    if (p.head.first == (N - 1) && p.head.second == (N - 1))
    {
        ans++;
        return;
    }

    Pipe tmp = p;
    switch (tmp.dir)
    {
    case 0:
        Move_Diagonal(tmp);
        Pipe_Move(tmp);

        tmp = p;
        Move_Horizontal(tmp);
        Pipe_Move(tmp);
        break;

    case 1:
        Move_Diagonal(tmp);
        Pipe_Move(tmp);

        tmp = p;
        Move_Vertical(tmp);
        Pipe_Move(tmp);
        break;

    case 2:
        Move_Diagonal(tmp);
        Pipe_Move(tmp);

        tmp = p;
        Move_Horizontal(tmp);
        Pipe_Move(tmp);

        tmp = p;
        Move_Vertical(tmp);
        Pipe_Move(tmp);
        break;
    }
}

int main()
{
    // initial Pipe
    Pipe p;
    p.dir = 0;
    p.head = make_pair(0, 1);
    p.tail = make_pair(0, 0);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
        }
    }

    Pipe_Move(p);

    cout << ans << "\n";
    
    return 0;
}