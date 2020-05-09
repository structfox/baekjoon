// 0 +, 1 -, 2 *, 3 /

#include <iostream>
#include <vector>

using namespace std;

int N;
int MIN = 0x3f3f3f3f;
int MAX = -0x3f3f3f3f;
vector<int> num;
vector<int> op;
vector<bool> used;

void Calc(int calculated, int depth)
{
    if (depth == num.size())
    {
        if (MIN > calculated) MIN = calculated;

        if (MAX < calculated) MAX = calculated;

        return;
    }
    int tmp = calculated;
    
    for (int i = 0; i < op.size(); i++)
    {
        if (used[i]) continue;

        calculated = tmp;
        used[i] = true;
        switch (op[i])
        {
        case 0:
            calculated += num[depth];
            break;
        case 1:
            calculated -= num[depth];
            break;
        case 2:
            calculated *= num[depth];
            break;
        case 3:
            calculated /= num[depth];
            break;
        }
        Calc(calculated, depth + 1);
        used[i] = false;
    }
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        num.push_back(tmp);
    }

    for (int i = 0; i < 4; i++)
    {
        int tmp;
        cin >> tmp;
        for (int j = 0; j < tmp; j++)
        {
            op.push_back(i);
            used.push_back(false);
        }
    }
    
    Calc(num[0], 1);
    
    cout << MAX << "\n" << MIN << "\n";
    return 0;
}