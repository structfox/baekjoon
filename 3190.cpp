// east 0, south 1, west 2, north 3

#include <iostream>
#include <deque>
#include <vector>
#include <cstring>

using namespace std;

const int dr[4] = {0, 1, 0, -1};
const int dc[4] = {1, 0, -1, 0};

int N, K, L;
int dir = 0;
char MOVE[10'001];
int MAP[101][101];
deque<pair<int,int> > snake;

int main()
{
    int cnt = 0;
    memset(MAP, 0, sizeof(MAP));
    memset(MOVE, 'G', sizeof(MOVE));

    cin >> N >> K;
    for (int i = 0; i < K; i++)
    {
        int r, c;
        cin >> r >> c;
        MAP[r][c] = 1;
    }
    cin >> L;
    for (int i = 0; i < L; i++)
    {
        int time;
        char ch;
        cin >> time >> ch;
        MOVE[time] = ch;
    }

    MAP[1][1] = 2;
    snake.push_back(make_pair(1, 1));

    while (true)
    {
        cnt++;

        int r = snake.back().first + dr[dir];
        int c = snake.back().second + dc[dir];

        // if head is out of range
        if (c > N || r > N || c < 1 || r < 1) break;

        // head hit body else
        if (MAP[r][c] == 2)
        {
            break;
        }
        else if (MAP[r][c] == 1) // where head location is apple
        {
            MAP[r][c] = 2;
            snake.push_back(make_pair(r, c));
        }
        else if (MAP[r][c] == 0) // head location is empty
        {
            MAP[r][c] = 2;
            snake.push_back(make_pair(r, c));

            r = snake.front().first;
            c = snake.front().second;
            MAP[r][c] = 0;
            snake.pop_front();
        }

        if (MOVE[cnt] == 'D')
        {
            ++dir;
            dir %= 4;
        }
        else if (MOVE[cnt]== 'L')
        {
            if (dir == 0)
            {
                dir = 3;
            }
            else
            {
                --dir;
            }
        }
    }

    cout << cnt << "\n";
    return 0;
}