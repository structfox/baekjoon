#include <iostream>
#include <queue>

const std::string endl = "\n";
const int MAX = 1001;

int map[MAX][MAX];
int N, M;

bool visited[MAX][MAX][2]; // {visited, breaked}
int cnt = 1;
std::pair<int, int> rc;

int main()
{
    // input
    std::cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            std::cin >> map[i][j];

    std::cout << -1 << endl;
    return 0;
}