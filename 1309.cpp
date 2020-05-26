#include <iostream>

using namespace std;

int N;
int DP[100'000];

int main()
{
    cin >> N;

    DP[0] = 1;
    DP[1] = 3;

    for (int i = 2; i <= N; i++)
    {
        DP[i] = (2*DP[i - 1] + DP[i - 2]) % 9901;
    }
    
    cout << DP[N] << "\n";
    return 0;
}