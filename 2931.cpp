#include <iostream>
#include <map>
/*
    ↑0, ↓1, ←2, →3
*/
char map[25][25];
std::pair<int, int> loc, Z, M; // coordination, direction from Z, direction from M
int dfz, dfm, R, C;
std::multimap<int, int> mm;

int DFS(std::pair<int, int>& l, const int& d) // coordination, 
{
    if (map[l.first][l.second] == '.')
        return d;

    mm.erase(mm.find({l.first, l.second}));

    switch (map[l.first][l.second])
    {
    case '|':
        if (d == 0)
        {
            --l.first;
            return DFS(l, 0);
        }
        else
        {
            ++l.first;
            return DFS(l, 1);
        }
        break;
    case '-':
        if (d == 2)
        {
            --l.second;
            return DFS(l, 2);
        }
        else
        {
            ++l.second;
            return DFS(l, 3);
        }
        break;
    case '+':
        if (d == 0)
        {
            --l.first;
            return DFS(l, 0);
        }
        else if (d == 1)
        {
            ++l.first;
            return DFS(l, 1);
        }
        else if (d == 2)
        {
            --l.second;
            return DFS(l, 2);
        }
        else if (d == 3)
        {
            ++l.second;
            return DFS(l, 3);
        }
        break;
    case '1':
        if (d == 0)
        {
            ++l.second;
            return DFS(l, 3);
        }
        else
        {
            ++l.first;
            return DFS(l, 1);
        }
        break;
    case '2':
        if (d == 1)
        {
            ++l.second;
            return DFS(l, 3);
        }
        else
        {
            --l.first;
            return DFS(l, 0);
        }
        break;
    case '3':
        if (d == 1)
        {
            --l.second;
            return DFS(l, 2);
        }
        else
        {
            --l.first;
            return DFS(l, 0);
        }
        break;
    case '4':
        if (d == 0)
        {
            --l.second;
            return DFS(l, 2);
        }
        else
        {
            ++l.first;
            return DFS(l, 1);
        }
        break;
    
    default:
        break;
    }
    return 0x3f3f3f3f;
}

int main()
{
    std::cin >> R >> C;
    for (int i = 0; i < R; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            std::cin >> map[i][j];

            if (map[i][j] != '.')
                mm.insert({i, j});

            if (map[i][j] == 'M')
            {
                M = {i, j};
                mm.erase(mm.find({i, j}));
            }
            else if (map[i][j] == 'Z')
            {
                Z = {i, j};
                mm.erase(mm.find({i, j}));
            }
        }
    }
    
    // find dfm
    if (M.first - 1 >= 0)
        if (map[M.first - 1][M.second] != '.' && map[M.first - 1][M.second] != '2' && map[M.first - 1][M.second] != '3' && map[M.first - 1][M.second] != '-')
        {
            loc = M;
            --loc.first;
            dfm = DFS(loc, 0);
        }

    if (M.first + 1 < R)
        if (map[M.first + 1][M.second] != '.' && map[M.first + 1][M.second] != '1' && map[M.first + 1][M.second] != '4' && map[M.first + 1][M.second] != '-')
        {
            loc = M;
            ++loc.first;
            dfm = DFS(loc, 1);
        }

    if (M.second - 1 >= 0)
        if (map[M.first][M.second - 1] != '.' && map[M.first][M.second - 1] != '3' && map[M.first][M.second - 1] != '4' && map[M.first][M.second - 1] != '|')
        {
            loc = M;
            --loc.second;
            dfm = DFS(loc, 2);
        }

    if (M.second + 1 < C)
        if (map[M.first][M.second + 1] != '.' && map[M.first][M.second + 1] != '1' && map[M.first][M.second + 1] != '2' && map[M.first][M.second + 1] != '|')
        {
            loc = M;
            ++loc.second;
            dfm = DFS(loc, 3);
        }

    // find dfz
    if (Z.first - 1 >= 0)
        if (map[Z.first - 1][Z.second] != '.' && map[Z.first - 1][Z.second] != '2' && map[Z.first - 1][Z.second] != '3' && map[Z.first - 1][Z.second] != '-')
        {
            loc = Z;
            --loc.first;
            dfz = DFS(loc, 0);
        }

    if (Z.first + 1 < R)
        if (map[Z.first + 1][Z.second] != '.' && map[Z.first + 1][Z.second] != '1' && map[Z.first + 1][Z.second] != '4' && map[Z.first + 1][Z.second] != '-')
        {
            loc = Z;
            ++loc.first;
            dfz = DFS(loc, 1);
        }

    if (Z.second - 1 >= 0)
        if (map[Z.first][Z.second - 1] != '.' && map[Z.first][Z.second - 1] != '3' && map[Z.first][Z.second - 1] != '4' && map[Z.first][Z.second - 1] != '|')
        {
            loc = Z;
            --loc.second;
            dfz = DFS(loc, 2);
        }

    if (Z.second + 1 < C)
        if (map[Z.first][Z.second + 1] != '.' && map[Z.first][Z.second + 1] != '1' && map[Z.first][Z.second + 1] != '2' && map[Z.first][Z.second + 1] != '|')
        {
            loc = Z;
            ++loc.second;
            dfz = DFS(loc, 3);
        }

    // output
    std::cout << loc.first + 1 << " " << loc.second + 1 << " ";

    if (!S.empty())
    {
        std::cout << "+" << "\n";
        return 0;
    }

    /*
    if (loc.first - 1 >= 0 && loc.second - 1 >= 0 && loc.first + 1 < R && loc.second + 1 < C)
        if (map[loc.first - 1][loc.second] != '.' && map[loc.first][loc.second + 1] != '.' && map[loc.first + 1][loc.second] != '.' && map[loc.first][loc.second - 1] != '.')
        {
            std::cout << "+" << " \n";
            return 0;
        }
    */
    
    if ((dfz == 0 && dfm == 1) || (dfz == 1 && dfm == 0))
        std::cout << "|" "\n";
    else if ((dfz == 2 && dfm == 3) || (dfz == 3 && dfm == 2))
        std::cout << "-" << "\n";
    else if ((dfz == 0 && dfm == 2) || (dfz == 2 && dfm == 0))
        std::cout << "1" << "\n";
    else if ((dfz == 1 && dfm == 2) || (dfz == 2 && dfm == 1))
        std::cout << "2" << "\n";
    else if ((dfz == 1 && dfm == 3) || (dfz == 3 && dfm == 1))
        std::cout << "3" << "\n";
    else if ((dfz == 0 && dfm == 3) || (dfz == 3 && dfm == 0))
        std::cout << "4" << "\n";

    return 0;
}