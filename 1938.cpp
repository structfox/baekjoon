#include <iostream>
#include <queue>

int map[50][50];
bool visit[50][50][2];
int N;
std::pair<int, int> E1, E2, E3;
class Tree
{
    public:
        // pair<row, column>
        std::pair<int, int> first, center, second;
        void Up();
        void Down();
        void Left();
        void Right();
        void Turn();
};
std::queue<std::pair<int, Tree>> Q;

bool isSafe(const Tree& T)
{
    if (T.first.first >= 0 && T.first.second >= 0 && T.first.first < N && T.first.second < N
    && T.center.first >= 0 && T.center.second >= 0 && T.center.first < N && T.center.second < N
    && T.second.first >= 0 && T.second.second >= 0 && T.second.first < N && T.second.second < N)
        if (map[T.first.first][T.first.second] != 1
        && map[T.center.first][T.center.second] != 1
        && map[T.second.first][T.second.second] != 1)
            return true;

    return false;
}

bool isSafeTurn(const Tree& T)
{
    if (T.first.first == T.second.first) // shape ---
    {
        if (T.first.first - 1 >= 0 && T.first.first + 1 < N)
            if (map[T.first.first - 1][T.first.second] == 0
            && map[T.center.first - 1][T.center.second] == 0
            && map[T.second.first - 1][T.second.second] == 0)
                if (map[T.first.first + 1][T.first.second] == 0
                && map[T.center.first + 1][T.center.second] == 0
                && map[T.second.first + 1][T.second.second] == 0)
                    return true;
    }
    else // shape |
        if (T.first.second - 1 >= 0 && T.first.second + 1 < N)
            if (map[T.first.first][T.first.second + 1] == 0
            && map[T.center.first][T.center.second + 1] == 0
            && map[T.second.first][T.second.second + 1] == 0)
                if (map[T.first.first][T.first.second - 1] == 0
                && map[T.center.first][T.center.second - 1] == 0
                && map[T.second.first][T.second.second - 1] == 0)
                    return true;

    return false;
}

void push_queue(const int& cnt, const Tree& T)
{
    if (T.first.first == T.second.first) // shape ---
    {
        if (visit[T.center.first][T.center.second][0] == false)
        {
            visit[T.center.first][T.center.second][0] = true;
            Q.push({cnt + 1, T});
        }
    }
    else //shape |
        if (visit[T.center.first][T.center.second][1] == false)
        {
            visit[T.center.first][T.center.second][1] = true;
            Q.push({cnt + 1, T});
        }
}

int main()
{
    int B_tmp = 0;
    int E_tmp = 0;
    int cnt = 0;
    Tree T;

    // input
    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            char temp;
            std::cin >> temp;
            if (temp == 'B')
            {
                switch (B_tmp)
                {
                case 0:
                    T.first.first = i;
                    T.first.second = j;
                    break;
                case 1:
                    T.center.first = i;
                    T.center.second = j;
                    break;
                case 2:
                    T.second.first = i;
                    T.second.second = j;
                    break;
                }
                ++B_tmp;
                map[i][j] = 0;
            }
            else if (temp == 'E')
            {
                switch (E_tmp)
                {
                case 0:
                    E1.first = i;
                    E1.second = j;
                    break;
                case 1:
                    E2.first = i;
                    E2.second = j;
                    break;
                case 2:
                    E3.first = i;
                    E3.second = j;
                    break;
                }
                ++E_tmp;
                map[i][j] = 0;
            }
            else
            {
                map[i][j] = temp - '0';
            }
        }
    }

    Q.push({cnt, T});
    visit[T.center.first][T.center.second][1] = true;

    while (!Q.empty())
    {
        cnt = Q.front().first;
        T = Q.front().second;
        Q.pop();

        if (T.first.first == E1.first && T.first.second == E1.second && T.center.first == E2.first && T.center.second == E2.second)
        {
            std::cout << cnt << "\n";
            return 0;
        }

        // bfs
        for (int i = 0; i < 5; ++i)
        {
            Tree nt = T;
            switch (i)
            {
            case 0:
                nt.Up();
                if (isSafe(nt))
                {
                    push_queue(cnt, nt);
                }
                break;
            case 1:
                nt.Down();
                if (isSafe(nt))
                {
                    push_queue(cnt, nt);
                }
                break;
            case 2:
                nt.Left();
                if (isSafe(nt))
                {
                    push_queue(cnt, nt);
                }
                break;
            case 3:
                nt.Right();
                if (isSafe(nt))
                {
                    push_queue(cnt, nt);
                }
                break;
            case 4:
                if (isSafeTurn(nt))
                {
                    nt.Turn();
                    push_queue(cnt, nt);
                }
                break;
            }
        }
    }
    // fail
    std::cout << 0 << "\n";
    return 0;
}

void Tree::Up()
{
    first.first -= 1;
    center.first -= 1;
    second.first -= 1;
}

void Tree::Down()
{
    first.first += 1;
    center.first += 1;
    second.first += 1;
}

void Tree::Left()
{
    first.second -= 1;
    center.second -= 1;
    second.second -= 1;
}

void Tree::Right()
{
    first.second += 1;
    center.second += 1;
    second.second += 1;
}

void Tree::Turn()
{
    first.first += 1;
    first.second -= 1;
    second.first -= 1;
    second.second += 1;
    std::swap(first, second);
}