#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Shark
{
    int r;
    int c;
    int speed;
    int dir;
    int size;
};

int R, C, M;
int ans = 0;
vector<Shark> V;

bool Sort_Shark(Shark A, Shark B)
{
    if (A.c <= B.c)
    {
        if (A.c == B.c)
        {
            if (A.r <= B.r)
            {
                if (A.r == B.r)
                {
                    if (A.size < B.size)
                    {
                        return true;
                    }
                    return false;
                }
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

void Catch_Shark(int c)
{
    bool checked = false;
    int tmp = 0x3f3f3f3f;
    vector<Shark>::iterator del;
    for (vector<Shark>::iterator i = V.begin(); i != V.end(); ++i)
    {
        if ((*i).c == c)
        {
            if (tmp > (*i).r)
            {
                tmp = (*i).r;
                del = i;
                checked = true;
            }
        }
    }
    if (checked)
    {
        ans += (*del).size;
        V.erase(del);
    }
}

void Shark_Move()
{
    int tmp;
    vector<Shark> alive_shark;
    for (int i = 0; i < V.size(); i++)
    {
        int speed = V[i].speed;
        if (V[i].dir == 1 || V[i].dir == 2)
        {
            speed %= (R - 1) * 2;
        }
        else if (V[i].dir == 3 || V[i].dir == 4)
        {
            speed %= (C - 1) * 2;
        }
        
        
        // move shark
        for (int j = 0; j < speed; j++)
        {
            switch (V[i].dir)
            {
            case 1:
                tmp = V[i].r;
                tmp--;
                if (tmp >= 0)
                {
                    V[i].r = tmp;
                }
                else
                {
                    V[i].r++;
                    V[i].dir = 2;
                }
                break;
            case 2:
                tmp = V[i].r;
                tmp++;
                if (tmp < R)
                {
                    V[i].r = tmp;
                }
                else
                {
                    V[i].r--;
                    V[i].dir = 1;
                }
                break;
            case 3:
                tmp = V[i].c;
                tmp++;
                if (tmp < C)
                {
                    V[i].c = tmp;
                }
                else
                {
                    V[i].c--;
                    V[i].dir = 4;
                }
                break;
            case 4:
                tmp = V[i].c;
                tmp--;
                if (tmp >= 0)
                {
                    V[i].c = tmp;
                }
                else
                {
                    V[i].c++;
                    V[i].dir = 3;
                }
                break;
            }
        }
    }

    // update shark;
    if (!V.empty())
    {
        sort(V.begin(), V.end(), Sort_Shark);
        Shark prev_shark = V[0];
        alive_shark.push_back(prev_shark);
        for (int i = 1; i < V.size(); i++)
        {
            if (prev_shark.r == V[i].r && prev_shark.c == V[i].c)
            {
                if (prev_shark.size < V[i].size)
                {
                    alive_shark.pop_back();
                }
                else
                {
                    continue;
                }
            }
            alive_shark.push_back(V[i]);
            prev_shark = V[i];
        }
        V.clear();
        V = alive_shark;
    }
}

int main()
{

    cin >> R >> C >> M;
    for (int i = 0; i < M; i++)
    {
        Shark tmp;
        cin >> tmp.r >> tmp.c >> tmp.speed >> tmp.dir >> tmp.size;
        tmp.r--;
        tmp.c--;
        V.push_back(tmp);
    }

    for (int i = 0; i < C; i++)
    {
        Catch_Shark(i);
        Shark_Move();
    }
    
    cout << ans << "\n";
    return 0;
}