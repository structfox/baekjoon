#include <iostream>
#include <queue>

using namespace std;

struct ball
{
    int cnt;
    pair<int, int> r;
    pair<int, int> b;
};

int N, M;
int ans = 0x3f3f3f3f;
pair<int, int> red;
pair<int, int> blue;
char MAP[10][10];
queue<ball> Q;

void move_right()
{
    if (blue.second > red.second)
    {
        // move blue
        while (true)
        {
            if (MAP[blue.first][blue.second] == 'O') break;
            if (MAP[blue.first][blue.second + 1] == '#') break;

            blue.second++;
        }

        // move red
        while (true)
        {
            if (MAP[red.first][red.second] == 'O') break;
            if (MAP[red.first][red.second + 1] == '#') break;
            if (blue.first == red.first && blue.second == (red.second + 1)) break;

            red.second++;
        }
    }
    else
    {
        //move red
        while (true)
        {
            if (MAP[red.first][red.second] == 'O') break;
            if (MAP[red.first][red.second + 1] == '#') break;

            red.second++;
        }

        // move blue
        while (true)
        {
            if (MAP[blue.first][blue.second] == 'O') break;
            if (MAP[blue.first][blue.second + 1] == '#') break;
            if (blue.first == red.first && (blue.second + 1) == red.second)
            {
                if (MAP[blue.first][blue.second + 1] == 'O')
                {
                    blue.second++;
                }
                break;
            }

            blue.second++;
        }
    }
}

void move_left()
{
    if (blue.second < red.second)
    {
        // move blue
        while (true)
        {
            if (MAP[blue.first][blue.second] == 'O') break;
            if (MAP[blue.first][blue.second - 1] == '#') break;

            blue.second--;
        }

        // move red
        while (true)
        {
            if (MAP[red.first][red.second] == 'O') break;
            if (MAP[red.first][red.second - 1] == '#') break;
            if (blue.first == red.first && blue.second == (red.second - 1)) break;

            red.second--;
        }
    }
    else
    {
        //move red
        while (true)
        {
            if (MAP[red.first][red.second] == 'O') break;
            if (MAP[red.first][red.second - 1] == '#') break;

            red.second--;
        }

        // move blue
        while (true)
        {
            if (MAP[blue.first][blue.second] == 'O') break;
            if (MAP[blue.first][blue.second - 1] == '#') break;
            if (blue.first == red.first && (blue.second - 1) == red.second)
            {
                if (MAP[blue.first][blue.second - 1] == 'O')
                {
                    blue.second--;
                }
                break;
            }

            blue.second--;
        }
    }
}

void move_up()
{
    if (blue.first < red.first)
    {
        // move blue
        while (true)
        {
            if (MAP[blue.first][blue.second] == 'O') break;
            if (MAP[blue.first - 1][blue.second] == '#') break;

            blue.first--;
        }

        // move red
        while (true)
        {
            if (MAP[red.first][red.second] == 'O') break;
            if (MAP[red.first - 1][red.second] == '#') break;
            if ((red.first - 1) == blue.first && blue.second == red.second) break;

            red.first--;
        }
    }
    else
    {
        //move red
        while (true)
        {
            if (MAP[red.first][red.second] == 'O') break;
            if (MAP[red.first - 1][red.second] == '#') break;

            red.first--;
        }

        // move blue
        while (true)
        {
            if (MAP[blue.first][blue.second] == 'O') break;
            if (MAP[blue.first - 1][blue.second] == '#') break;
            if ((blue.first - 1) == red.first && blue.second == red.second)
            {
                if (MAP[blue.first - 1][blue.second] == 'O')
                {
                    blue.first--;
                }
                break;
            }

            blue.first--;
        }
    }
}

void move_down()
{
    if (blue.first > red.first)
    {
        // move blue
        while (true)
        {
            if (MAP[blue.first][blue.second] == 'O') break;
            if (MAP[blue.first + 1][blue.second] == '#') break;

            blue.first++;
        }

        // move red
        while (true)
        {
            if (MAP[red.first][red.second] == 'O') break;
            if (MAP[red.first + 1][red.second] == '#') break;
            if (blue.first == (red.first + 1) && blue.second == red.second) break;

            red.first++;
        }
    }
    else
    {
        //move red
        while (true)
        {
            if (MAP[red.first][red.second] == 'O') break;
            if (MAP[red.first + 1][red.second] == '#') break;

            red.first++;
        }

        // move blue
        while (true)
        {
            if (MAP[blue.first][blue.second] == 'O') break;
            if (MAP[blue.first + 1][blue.second] == '#') break;
            if ((blue.first + 1) == red.first && blue.second == red.second)
            {
                if (MAP[blue.first + 1][blue.second] == 'O')
                {
                    blue.first++;
                }
                break;
            }

            blue.first++;
        }
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == 'B')
            {
                MAP[i][j] = '.';
                blue = make_pair(i, j);
            }
            if (MAP[i][j] == 'R')
            {
                MAP[i][j] = '.';
                red = make_pair(i, j);
            }
        }
    }

    ball start;
    start.cnt = 0;
    start.b = blue;
    start.r = red;
    Q.push(start);

    while (!Q.empty())
    {
        start.cnt = Q.front().cnt;
        start.b = Q.front().b;
        start.r = Q.front().r;
        Q.pop();

        if (start.cnt > 10) break;
        if (MAP[start.b.first][start.b.second] == 'O') continue;
        if (MAP[start.r.first][start.r.second] == 'O')
        {
            ans = start.cnt;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            ball tmp;
            tmp.cnt = start.cnt + 1;
            red = start.r;
            blue = start.b;

            switch (i)
            {
            case 0:
                move_right();
                tmp.r = red;
                tmp.b = blue;
                Q.push(tmp);
                break;
            case 1:
                move_left();
                tmp.r = red;
                tmp.b = blue;
                Q.push(tmp);
                break;
            case 2:
                move_up();
                tmp.r = red;
                tmp.b = blue;
                Q.push(tmp);
                break;
            case 3:
                move_down();
                tmp.r = red;
                tmp.b = blue;
                Q.push(tmp);
                break;
            }
        }
    }

    if (ans > 10) ans = -1;

    cout << ans << "\n";
    
    return 0;
}