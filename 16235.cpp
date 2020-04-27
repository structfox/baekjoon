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
vector<int> trees[10][10];

void Spring_Summer()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (trees[i][j].size() == 0) continue;

            int dead_ingredient = 0;
            vector<int> tmp;
            sort(trees[i][j].begin(), trees[i][j].end());

            // eat ingredient
            for (int k = 0; k < trees[i][j].size(); k++)
            {
                // have enough ingredient
                if (MAP[i][j] >= trees[i][j][k])
                {
                    MAP[i][j] -= trees[i][j][k];
                    tmp.push_back(trees[i][j][k] + 1);
                }
                else
                {
                    dead_ingredient += static_cast<int>(trees[i][j][k] / 2);
                }
            }

            trees[i][j].clear();
            for (int k = 0; k < tmp.size(); k++)
            {
                trees[i][j].push_back(tmp[k]);
            }

            MAP[i][j] += dead_ingredient;
        }
    }
}

void Autumn_Winter()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < trees[i][j].size(); k++)
            {
                if (trees[i][j][k] % 5 == 0) //autumn
                {
                    if (i - 1 >= 0)
                    {
                        if (j - 1 >= 0) trees[i - 1][j - 1].push_back(1); //.insert(trees[i - 1][j - 1].begin(), make_pair(1, 1));

                        if (j + 1 < N) trees[i - 1][j + 1].push_back(1); //.insert(trees[i - 1][j + 1].begin(), make_pair(1, 1));

                        trees[i - 1][j].push_back(1); // .insert(trees[i - 1][j].begin(), make_pair(1, 1));
                    }

                    if (i + 1 < N)
                    {
                        if (j - 1 >= 0) trees[i + 1][j - 1].push_back(1); // .insert(trees[i + 1][j - 1].begin(), make_pair(1, 1));
                        
                        if (j + 1 < N) trees[i + 1][j + 1].push_back(1); // .insert(trees[i + 1][j + 1].begin(), make_pair(1, 1));

                        trees[i + 1][j].push_back(1); // .insert(trees[i + 1][j].begin(), make_pair(1, 1));
                    }

                    if (j - 1 >= 0) trees[i][j - 1].push_back(1); //.insert(trees[i][j - 1].begin(), make_pair(1, 1));

                    if (j + 1 < N) trees[i][j + 1].push_back(1); // .insert(trees[i][j + 1].begin(), make_pair(1, 1));
                }
            }
            MAP[i][j] += A[i][j]; // winter
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
            cin >> A[i][j];
            MAP[i][j] = 5;
        }
    }

    // N * N array with vector<pair<death, age>> initial 
    for (int i = 0; i < M; i++)
    {
        int r, c, a;
        cin >> r >> c >> a;
        trees[r - 1][c - 1].push_back(a);
    }
    
    for (int i = 0; i < K; i++)
    {
        Spring_Summer();
        Autumn_Winter();
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