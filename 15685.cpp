#include <iostream>
#include <vector>

using namespace std;

const int dy[4] = {0, -1, 0, 1};
const int dx[4] = {1, 0, -1, 0};

int N, x, y, d, g;
int answer = 0;
int MAP[101][101];
vector<int> dragon;

void Curve()
{
    int s = dragon.size();
    for (int i = s - 1; i >= 0; i--)
    {
        int nd = (dragon[i] + 1) % 4;
        x += dx[nd];
        y += dy[nd];
        MAP [y][x] = 1;

        dragon.push_back(nd);
    }
}

void Count()
{
    for (int i = 0; i <= 100; i++)
    {
        for (int j = 0; j <= 100; j++)
        {
            if (MAP[i][j] == 1)
            {
                if (MAP[i + 1][j] == 1 && MAP[i][j + 1] == 1 && MAP[i + 1][j + 1] == 1) ++answer;
            }
        }
    }
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> x >> y >> d >> g;
        dragon.clear();

        MAP[y][x] = 1;
        x += dx[d];
        y += dy[d];
        MAP[y][x] = 1;

        dragon.push_back(d);
        for (int i = 0; i < g; i++)
        {
            Curve();
        }
    }
    
    Count();

    cout << answer << "\n";
    return 0;
}