#include <iostream>
using namespace std;

int main()
{
    int N;
    int dp[12];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;

    for (int i = 4; i < 12; ++i)
    {
        dp[i] = dp[i - 3] + dp[i - 2] + dp[i - 1];
    }

    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int tmp;
        cin >> tmp;
        cout << dp[tmp] << "\n";
    }

    return 0;
}