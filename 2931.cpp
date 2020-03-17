#include <iostream>
#include <set>
/*
    ↑0, ↓1, ←2, →3
*/
char map[25][25];
std::pair<int, int> loc_m, loc_z, Z, M; // coordination, direction from Z, direction from M
int dfz, dfm, R, C;
std::set<std::pair<int, int>> S;

int DFS(std::pair<int, int>& l, const int& d) // coordination, 
{
    if (map[l.first][l.second] == '.')
        return d;
    
    if (S.find(l) != S.end())
        S.erase(S.find(l));

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

void Find_loc(const std::pair<int, int>& S, std::pair<int, int> &l, int& d)
{
    l = S;

    if (S.first - 1 >= 0)
        if (map[S.first - 1][S.second] != '.' && map[S.first - 1][S.second] != '2' && map[S.first - 1][S.second] != '3' && map[S.first - 1][S.second] != '-')
        {
            --l.first;
            d = DFS(l, 0);
        }

    if (S.first + 1 < R)
        if (map[S.first + 1][S.second] != '.' && map[S.first + 1][S.second] != '1' && map[S.first + 1][S.second] != '4' && map[S.first + 1][S.second] != '-')
        {
            ++l.first;
            d = DFS(l, 1);
        }

    if (S.second - 1 >= 0)
        if (map[S.first][S.second - 1] != '.' && map[S.first][S.second - 1] != '3' && map[S.first][S.second - 1] != '4' && map[S.first][S.second - 1] != '|')
        {
            --l.second;
            d = DFS(l, 2);
        }

    if (S.second + 1 < C)
        if (map[S.first][S.second + 1] != '.' && map[S.first][S.second + 1] != '1' && map[S.first][S.second + 1] != '2' && map[S.first][S.second + 1] != '|')
        {
            ++l.second;
            d = DFS(l, 3);
        }
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
                S.insert(std::make_pair(i, j));

            if (map[i][j] == 'M')
            {
                M = {i, j};
                S.erase(std::make_pair(i, j));
            }
            else if (map[i][j] == 'Z')
            {
                Z = {i, j};
                S.erase(std::make_pair(i, j));
            }
        }
    }

    Find_loc(M, loc_m, dfm);

    Find_loc(Z, loc_z, dfz);

    if (loc_m != loc_z)
    {
        std::cout << -1 << "\n";
        return 0;
    }
    // output
    std::cout << loc_m.first + 1 << " " << loc_m.second + 1 << " ";

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