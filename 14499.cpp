#include <iostream>
#include <vector>
#include <algorithm>

int dice[6] = {0, 0, 0, 0, 0, 0};
int x, y; // current location
int N, M, K;
std::vector<std::vector<int>> map;

void rotate(int direction);
void copy();
void move(int direction);

int main()
{
    int direction;

    std::cin >> N >> M >> x >> y >> K;
    for (int i = 0; i < N; ++i)
    {
        int temp_num;
        std::vector<int> temp_map;
        for (int j = 0; j < M; ++j)
            {
                std::cin >> temp_num;
                temp_map.push_back(temp_num);
            }
        map.push_back(temp_map);
    }

    for (int i = 0; i < K; ++i)
    {
        std::cin >> direction;
        move(direction);
    }

    return 0;
}

void rotate(int direction)
{
    switch (direction)
    {
        // east
        case 1:
            std::swap(dice[0], dice[3]);
            std::swap(dice[0], dice[5]);
            std::swap(dice[0], dice[2]);
            break;

        // west
        case 2:
            std::swap(dice[0], dice[2]);
            std::swap(dice[0], dice[5]);
            std::swap(dice[0], dice[3]);
            break;

        // north
        case 3:
            std::swap(dice[0], dice[1]);
            std::swap(dice[0], dice[5]);
            std::swap(dice[0], dice[4]);
            break;

        // south
        case 4:
            std::swap(dice[0], dice[4]);
            std::swap(dice[0], dice[5]);
            std::swap(dice[0], dice[1]);
            break;
    }
}

void copy()
{
    if (map[y][x] == 0)
        map[y][x] = dice[5];
    else
        {
            dice[5] = map[y][x];
            map[y][x] = 0;
        }
}

void move(int direction)
{
    int nx = x, ny = y;
    // move current location
    switch(direction)
    {
        case 1:
            ++nx;
            break;
        
        case 2:
            --nx;
            break;
        
        case 3:
            --ny;
            break;
        
        case 4:
            ++ny;
            break;
    }

    // if current location is out of map, do nothing.
    if (nx >= M || ny >= N || nx < 0 || ny < 0) {}
    else
    {
        x = nx;
        y = ny;
        rotate(direction);
        copy();
        std::cout << dice[0] << "\n";
    }
}