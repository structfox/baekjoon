#include <iostream>
#include <vector>
#include <queue>

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l, const std::pair<T,U> & r) {   
    return {l.first + r.first, l.second + r.second};                                    
}       

int main()
{
    int L, N;
    std::pair<int, int> current_loc = {0, 0};
    int next_dir = 0;
    std::queue<int> dir;
    // DIR {east, north, west, south}
    const std::pair<int, int> DIR[4] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    char pos;
    std::vector<std::pair<int, int>> map;
    map.push_back(current_loc);
    int cnt = 0;

    // dir.push(next_dir);
    std::cin >> L >> N;
    for (int i = 0; i < N; ++i)
    {
        int temp;
        std::cin >> temp >> pos;

        for (int j = 0; j < temp; ++j)
        {
            dir.push(next_dir);
        }

        // change next_dir
        if (pos == 'L')
            next_dir = (next_dir + 1) % 4;
        else if (pos == 'R')
        {
            if (next_dir == 0)
                next_dir = 3;
            else
                --next_dir;
        }
    }

    for(;;)
    {
        int temp_dir = dir.front();
        dir.pop();

        ++cnt;
        current_loc = current_loc + DIR[temp_dir];

        // check if snake escaped from the map
        if (current_loc.first > L || current_loc.first < -L || current_loc.second > L || current_loc.second < -L)
            goto end;

        // check if snake hit it's body
        for (int i = 0; i < map.size(); ++i)
        {
            if (map[i] == current_loc)
                goto end;
        }

        map.push_back(current_loc);
        dir.push(next_dir);
    }

    end:
    std::cout << cnt << '\n';

    return 0;
}