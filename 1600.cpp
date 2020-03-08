#include <iostream>
#include <queue>
#include <vector>

int m_move_c[4] = {1, -1, 0, 0};
int m_move_r[4] = {0, 0, 1, -1};
int h_move_c[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int h_move_r[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

int main()
{
    int K, W, H;
    std::vector<std::vector<int>> map;
    
    std::cin >> K >> W >> H;
    // map input
    for (int i = 0; i < H; ++i)
    {
        std::vector<int> v_temp;
        for (int j = 0; j < W; ++j)
        {
            int i_temp;
            std::cin >> i_temp;
            v_temp.push_back(i_temp);
        }
        map.push_back(v_temp);
    }

    // visit[H][W][K + 1] need to set as 'K + 1' because the range of 'horse move count' can be 0 ~ K
    std::vector<std::vector<std::vector<bool>>> visit(H, std::vector<std::vector<bool>>(W, std::vector<bool>(K + 1, false)));
    /*
    for (int i = 0; i < H; ++i)
    {
        std::vector<std::vector<bool>> v_temp_1;
        for (int j = 0; j < W; ++j)
        {
            std::vector<bool> v_temp_2(K + 1, false);
            v_temp_1.push_back(v_temp_2);
        }
        visit.push_back(v_temp_1);
    }
    */

    visit[0][0][0] = true;

    // queue<{{r, c}, {cnt, h_move}}
    std::queue<std::pair<std::pair<int, int>, std::pair<int, int>>> Q;
    Q.push({{0, 0}, {0, 0}});

    while (!Q.empty())
    {
        // row, column, total move count, horse move count
        int r = Q.front().first.first, c = Q.front().first.second, cnt = Q.front().second.first, h_move = Q.front().second.second;
        Q.pop();

        if (r == H - 1 && c == W -1)
        {
            std::cout << cnt << "\n";
            return 0;
        }

        // check with horse move
        if (h_move < K)
        {
            for (int i = 0; i < 8; ++i)
            {
                int nr, nc;
                nr = r + h_move_r[i];
                nc = c + h_move_c[i];

                // nr, nc is in map range, not yet visited with h_move + 1 move, not blocked
                if (nr >= 0 && nc >= 0 && nr < H && nc < W && map[nr][nc] == 0 && !visit[nr][nc][h_move + 1])
                {
                    visit[nr][nc][h_move + 1] = true;
                    Q.push({{nr, nc}, {cnt + 1, h_move + 1}});
                }
            }
        }

        // check with monkey move
        for (int i = 0; i < 4; ++i)
        {
            int nr, nc;
            nr = r + m_move_r[i];
            nc = c + m_move_c[i];

            // nr, nc is in map range, not yet visited with h_move move, not blocked
            if (nr >= 0 && nc >= 0 && nr < H && nc < W && map[nr][nc] == 0 && !visit[nr][nc][h_move])
            {
                visit[nr][nc][h_move] = true;
                Q.push({{nr, nc}, {cnt + 1, h_move}});
            }
        }
    }

    // fixed to -1 from 'fail'
    std::cout << -1 << "\n";

    return 0;
}