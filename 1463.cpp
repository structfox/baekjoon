#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int num;
    queue<pair<int, int> > Q;
    cin >> num;

    Q.push(make_pair(num, 0));
    while (!Q.empty())
    {
        int tmp = Q.front().first;
        int cnt = Q.front().second;
        Q.pop();

        if (tmp == 1)
        {
            cout << cnt << "\n";
            break;
        }

        for (int i = 0; i < 3; i++)
        {
            num = tmp;
            switch (i)
            {
            case 0:
                if (num % 3 == 0)
                {
                    num /= 3;
                    if (num > 0)
                    {
                        Q.push(make_pair(num, cnt + 1));
                    }
                }
                break;
            case 1:
                if (num % 2 == 0)
                {
                    num /= 2;
                    if (num > 0)
                    {
                        Q.push(make_pair(num, cnt + 1));
                    }
                }
                break;
            case 2:
                --num;
                if (num > 0)
                {
                    Q.push(make_pair(num, cnt + 1));
                }
                break;
            }
        }
    }
    
    return 0;
}