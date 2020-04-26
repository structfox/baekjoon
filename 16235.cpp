#include <iostream>
#include <vector>

using namespace std;

int N, M, K;
int MAP[10][10];
int A[10][10];
vector<pair<pair<int, int>, pair<int, int>>> trees; // tree (age, dead), (r, c) 0:dead, 1:alive

void spring()
{
    int age = 0x3f3f3f3f;
    int tree_num;
    for (int i = 0; i < trees.size(); i++)
    {
        if (!trees[i].first.second) continue;
        if (MAP[trees[i].second.first][trees[i].second.second] < trees[i].first.first)
        {
            trees[i].first.second = 0;
        }
        else
        {
            if (age > trees[i].first.first)
            {
                tree_num = i;
                age = trees[i].first.first;
            }
        }
    }
    // decrease ingredient
    MAP[trees[tree_num].second.first][trees[tree_num].second.second] -= trees[tree_num].first.first;
}

void summer()
{
    int size = trees.size();
    for (int i = 0; i < size; i++)
    {
        if (trees[i].first.second) continue;
        MAP[trees[i].second.first][trees[i].second.second] += (trees[i].first.first / 2);
    }
}

void autumn()
{
    int tree_size = trees.size();
    for (int i = 0; i < tree_size; i++)
    {
        if (!(trees[i].first.first % 5))
        {
        }
    }
}

void winter()
{
    for (int i = 0; i < N; i++)
    {
        MAP[i][i] += A[i][i];
    }
}


int main()
{
    // input
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        A[i][i] = tmp;
    }
    for (int i = 0; i < M; i++)
    {
        int r, c, a;
        cin >> r >> c >> a;
        trees.push_back(make_pair(make_pair(a, 1), make_pair(r, c)));
    }
    
    for (int i = 0; i < K; i++)
    {
        spring();
        summer();
        autumn();
        winter();
        for (int i = 0; i < trees.size(); i++)
        {
            trees[i].first.first++;
        }
    }

    return 0;
}