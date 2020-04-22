/*
    0 north, 1 east, 2 south, 3 west
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX = 8;

int N, M;
int answer = 0x3f3f3f3f;
int MAP[MAX][MAX];
int C_MAP[MAX][MAX];
vector<pair<int, int> > cctv;

void Copy_Map(int m_MAP[MAX][MAX])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            C_MAP[i][j] = m_MAP[i][j];
        }
    }
}

void CC1(int dir, int r, int c)
{
    switch (dir)
    {
    case 0: // north
        --r;
        while (r >= 0)
        {
            if (C_MAP[r][c] == 6) break;
            
            if (C_MAP[r][c] == 0) C_MAP[r][c] = -1;
            --r;
        }
        break;

    case 1: // east
        ++c;
        while (c < M)
        {
            if (C_MAP[r][c] == 6) break;
            
            if (C_MAP[r][c] == 0) C_MAP[r][c] = -1;
            ++c;
        }
        break;
    
    case 2: // south
        ++r;
        while (r < N)
        {
            if (C_MAP[r][c] == 6) break;
            
            if (C_MAP[r][c] == 0) C_MAP[r][c] = -1;
            ++r;
        }
        break;
    case 3: // west
        --c;
        while (c >= 0)
        {
            if (C_MAP[r][c] == 6) break;
            
            if (C_MAP[r][c] == 0) C_MAP[r][c] = -1;
            --c;
        }
        break;
    }
}

void CC2(int dir, int r, int c)
{
    CC1(dir, r, c);
    CC1((dir + 2) % 4, r, c);
}

void CC3(int dir, int r, int c)
{
    CC1(dir, r, c);
    CC1((dir + 3) % 4, r, c);
}

void CC4(int dir, int r, int c)
{
    CC1(dir, r, c);
    CC1((dir + 2) % 4, r, c);
    CC1((dir + 3) % 4, r, c);
}

void CC5(int dir, int r, int c)
{
    CC1(dir, r, c);
    CC1((dir + 1) % 4, r, c);
    CC1((dir + 2) % 4, r, c);
    CC1((dir + 3) % 4, r, c);
}

int Count()
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (C_MAP[i][j] == 0) ++cnt;
        }
    }
    return cnt;
}

void Roll(int m_MAP[MAX][MAX], int cctv_cnt)
{
    if (cctv_cnt >= cctv.size())
    {
        int cnt = Count();
        answer = (answer < cnt) ? answer : cnt;
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        switch (C_MAP[cctv[cctv_cnt].first][cctv[cctv_cnt].second])
        {
        case 1:
            CC1(i, cctv[cctv_cnt].first, cctv[cctv_cnt].second);
            Roll(C_MAP, cctv_cnt + 1);
            Copy_Map(m_MAP);
            break;

        case 2:
            CC2(i, cctv[cctv_cnt].first, cctv[cctv_cnt].second);
            Roll(C_MAP, cctv_cnt + 1);
            Copy_Map(m_MAP);
            break;

        case 3:
            CC3(i, cctv[cctv_cnt].first, cctv[cctv_cnt].second);
            Roll(C_MAP, cctv_cnt + 1);
            Copy_Map(m_MAP);
            break;

        case 4:
            CC4(i, cctv[cctv_cnt].first, cctv[cctv_cnt].second);
            Roll(C_MAP, cctv_cnt + 1);
            Copy_Map(m_MAP);
            break;
        
        case 5:
            CC5(i, cctv[cctv_cnt].first, cctv[cctv_cnt].second);
            Roll(C_MAP, cctv_cnt + 1);
            Copy_Map(m_MAP);
            break;
        }
    }
    
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] != 0 && MAP[i][j] != 6)
            {
                cctv.push_back(make_pair(i, j));
            }
        }
    }

    Copy_Map(MAP);
    Roll(MAP, 0);

    cout << answer << "\n";
    
    return 0;
}