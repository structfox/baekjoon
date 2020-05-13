#include <iostream>
using namespace std;

int main()
{
    int N;
    long long ans = 0;
    long long dp[101][10];
    dp[1][0] = 0;
    dp[1][1] = 1;
    dp[1][2] = 1;
    dp[1][3] = 1;
    dp[1][4] = 1;
    dp[1][5] = 1;
    dp[1][6] = 1;
    dp[1][7] = 1;
    dp[1][8] = 1;
    dp[1][9] = 1;

    cin >> N;

    for (int i = 2; i <= N; ++i)
    {
        dp[i][0] = dp[i - 1][1] % 1000000000;
        dp[i][9] = dp[i - 1][8] % 1000000000;
        for (int j = 1; j < 9; ++j)
        {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1]) % 1000000000;
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        ans += dp[N][i];
    }

    ans %= 1000000000;

    cout << ans;
    return 0;
}