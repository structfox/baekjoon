#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 15;

int N;
int answer = -0x3f3f3f3f;
int T[MAX];
int P[MAX];

/*
void Cal(int day, int sum)
{
    if (day >= N + 1)
    {
        answer = (answer > sum) ? answer : sum;
        return;
    }

    if (day + T[day - 1] <= N + 1) Cal(day + T[day - 1], sum + P[day - 1]);

    if (day + 1 <= N + 1) Cal(day + 1, sum);
}
*/

void Cal(int day, int sum)
{
    answer = (answer > sum) ? answer : sum;

    for (int i = 0; i < N; i++)
    {
        
    }
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> T[i] >> P[i];
    }

    Cal(1, 0);
    
    cout << answer << "\n";
    
    return 0;
}