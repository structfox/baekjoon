#include <iostream>
#include <vector>

using namespace std;

int N, M;
int answer = 0x3f3f3f3f;
vector<bool> open;
vector<int> chicken_road;
vector<pair<int, int> > home;
vector<pair<int, int> > chicken;

int Distance(pair<int, int> a, pair<int, int> b)
{
    int d = 0;
    if (a.first > b.first)
    {
        d += (a.first - b.first);
    }
    else
    {
        d += (b.first - a.first);
    }

    if (a.second > b.second)
    {
        d += (a.second - b.second);
    }
    else
    {
        d += (b.second - a.second);
    }
    return d;
}

void Close_Chicken(int idx, int cnt)
{
    if (cnt > M)
    {
        int sum = 0;
        for (int i = 0; i < chicken.size(); i++)
        {
            if (open[i])
            {
                for (int j = 0; j < home.size(); j++)
                {
                    int tmp = Distance(chicken[i], home[j]);

                    chicken_road[j] = (chicken_road[j] < tmp) ? chicken_road[j] : tmp;
                }
            }
        }

        for (int i = 0; i < chicken_road.size(); i++)
        {
            sum += chicken_road[i];
        }
        
        chicken_road = vector<int>(home.size(), 0x3f3f3f3f);

        answer = (answer < sum) ? answer : sum;
        return;
    }
    
    for (int i = idx; i < chicken.size() - M + cnt; i++)
    {
        open[i] = true;
        Close_Chicken(i + 1, cnt + 1);
        open[i] = false;
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int tmp;
            cin >> tmp;
            if (tmp == 1)
            {
                home.push_back(make_pair(i,j));
            }
            else if (tmp == 2)
            {
                chicken.push_back(make_pair(i, j));
            }
        }
    }

    chicken_road = vector<int>(home.size(), 0x3f3f3f3f);
    open = vector<bool>(chicken.size(), false);

    Close_Chicken(0, 1);

    cout << answer <<"\n";
    return 0;
}