/*
death(0: death, 1: alive), age
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, K;
int MAP[10][10];
int A[10][10];

void spring(vector<vector<vector<pair<int, int>>>>& trees)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // eat ingredient
            for (int k = 0; k < trees[i][j].size(); k++)
            {
                // if tree is dead
                if (trees[i][j][k].first == 0) continue;
                
                // have enough ingredient
                if (MAP[i][j] >= trees[i][j][k].second)
                {
                    MAP[i][j] -= trees[i][j][k].second;
                }
                else
                {
                    trees[i][j][k].first = 0;
                }
            }
        }
    }
}

void summer(vector<vector<vector<pair<int, int>>>>& trees)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (vector<pair<int, int>>::iterator k = trees[i][j].begin(); k != trees[i][j].end(); k++)
            {
                // if tree is alive
                if ((*k).first == 1) continue;

                MAP[i][j] += static_cast<int>((*k).second / 2);
                trees[i][j].erase(k);

                --k;
            }
        }
    }
}

void autumn(vector<vector<vector<pair<int, int>>>>& trees)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < trees[i][j].size(); k++)
            {
                // tree's age is multiples of 5
                if (trees[i][j][k].second % 5 == 0)
                {
                    if (i - 1 >= 0)
                    {
                        if (j - 1 >= 0) trees[i - 1][j - 1].insert(trees[i - 1][j - 1].begin(), make_pair(1, 0));

                        if (j + 1 < N) trees[i - 1][j + 1].insert(trees[i - 1][j + 1].begin(), make_pair(1, 0));

                        trees[i - 1][j].insert(trees[i - 1][j].begin(), make_pair(1, 0));
                    }

                    if (i + 1 < N)
                    {
                        if (j - 1 >= 0) trees[i + 1][j - 1].insert(trees[i + 1][j - 1].begin(), make_pair(1, 0));
                         
                        if (j + 1 < N) trees[i + 1][j + 1].insert(trees[i + 1][j + 1].begin(), make_pair(1, 0));

                        trees[i + 1][j].insert(trees[i + 1][j].begin(), make_pair(1, 0));
                    }

                    if (j - 1 >= 0) trees[i][j - 1].insert(trees[i][j - 1].begin(), make_pair(1, 0));

                    if (j + 1 < N) trees[i][j + 1].insert(trees[i][j + 1].begin(), make_pair(1, 0));
                }
            }
        }
    }
}

void winter(vector<vector<vector<pair<int, int>>>>& trees)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < trees[i][j].size(); k++)
            {
                ++trees[i][j][k].second;
            }
            
            MAP[i][j] += A[i][j];
        }
    }
}


int main()
{
    // input
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int tmp;
            cin >> tmp;
            A[i][j] = tmp;
            MAP[i][j] = 5;
        }
    }
    // N * N array with vector<pair<death, age>> initial 
    vector<vector<vector<pair<int, int>>>> trees(N, vector<vector<pair<int, int>>>(N, vector<pair<int, int>>(0)));
    for (int i = 0; i < M; i++)
    {
        int r, c, a;
        cin >> r >> c >> a;
        trees[r - 1][c - 1].push_back(make_pair(1, a));
    }
    
    for (int i = 0; i < K; i++)
    {
        spring(trees);
        summer(trees);
        autumn(trees);
        winter(trees);
    }

    int answer = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            answer += trees[i][j].size();
        }
    }

    cout << answer << "\n";
    return 0;
}