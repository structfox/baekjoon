/*
    0 north, 1 east, 2 south, 3 west

    0 empty, space 1 wall, 2 cleaned
*/
#include <iostream>
using namespace std;

const int MAX = 50;
const pair<int, int> north = {-1, 0};
const pair<int, int> east = {0, 1};
const pair<int, int> south = {1, 0};
const pair<int, int> west = {0, -1};

int N, M, dir;
int MAP[MAX][MAX];
pair<int, int> loc;

void Clean()
{
    int turn_count = 0;
    while (true)
    {
        // stop cleaning
        if (turn_count == 4)
        {
            switch (dir)
            {
            case 0:
                if (loc.first + 1 >= N) return;
                else
                {
                    if (MAP[loc.first + 1][loc.second] == 1) return;
                    ++loc.first;
                    turn_count = 0;
                }
                break;

            case 1:
                if (loc.second - 1 < 0) return;
                else
                {
                    if (MAP[loc.first][loc.second - 1] == 1) return;
                    --loc.second;
                    turn_count = 0;
                }
                break;
            
            case 2:
                if (loc.first - 1 < 0) return;
                else
                {
                    if (MAP[loc.first - 1][loc.second] == 1) return;
                    --loc.first;
                    turn_count = 0;
                }
                break;

            case 3:
                if (loc.second + 1 >= M) return;
                else
                {
                    if (MAP[loc.first][loc.second + 1] == 1) return;
                    ++loc.second;
                    turn_count = 0;
                }
                break;
            }
        }

        switch (dir)
        {
        case 0:
            if (loc.second - 1 < 0)
            {
                dir = (dir + 3) % 4;
                ++turn_count;
            }
            else
            {
                if (MAP[loc.first][loc.second - 1] == 1 || MAP[loc.first][loc.second - 1] == 2)
                {
                    dir = (dir + 3) % 4;
                    ++turn_count;
                }
                else
                {
                    turn_count = 0;
                    dir = (dir + 3) % 4;
                    --loc.second;
                    MAP[loc.first][loc.second] = 2;
                }
            }
            break;
        case 1:
            if (loc.first - 1 < 0)
            {
                dir = (dir + 3) % 4;
                ++turn_count;
            }
            else
            {
                if (MAP[loc.first - 1][loc.second] == 1 || MAP[loc.first - 1][loc.second] == 2)
                {
                    dir = (dir + 3) % 4;
                    ++turn_count;
                }
                else
                {
                    turn_count = 0;
                    dir = (dir + 3) % 4;
                    --loc.first;
                    MAP[loc.first][loc.second] = 2;
                }
            }
            break;
        case 2:
            if (loc.second + 1 >= M)
            {
                dir = (dir + 3) % 4;
                ++turn_count;
            }
            else
            {
                if (MAP[loc.first][loc.second + 1] == 1 || MAP[loc.first][loc.second + 1] == 2)
                {
                    dir = (dir + 3) % 4;
                    ++turn_count;
                }
                else
                {
                    turn_count = 0;
                    dir = (dir + 3) % 4;
                    ++loc.second;
                    MAP[loc.first][loc.second] = 2;
                }
            }
            break;
        case 3:
            if (loc.first + 1 >= N)
            {
                dir = (dir + 3) % 4;
                ++turn_count;
            }
            else
            {
                if (MAP[loc.first + 1][loc.second] == 1 || MAP[loc.first + 1][loc.second] == 2)
                {
                    dir = (dir + 3) % 4;
                    ++turn_count;
                }
                else
                {
                    turn_count = 0;
                    dir = (dir + 3) % 4;
                    ++loc.first;
                    MAP[loc.first][loc.second] = 2;
                }
            }
            break;
        }
    }
}

int Count()
{
    int cnt = 0;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (MAP[i][j] == 2)
            {
                ++cnt;
            }

    return cnt;
}

int main()
{
    int answer;

    // input
    cin >> N >> M;
    cin >> loc.first >> loc.second >> dir;
    // loc.first--; loc.second--;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
        }
    }
    // first loc clean
    MAP[loc.first][loc.second] = 2;

    Clean();
    answer = Count();

    cout << answer << "\n";

    return 0;
}