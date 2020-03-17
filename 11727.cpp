#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    int dp[1000];
    dp[0] = 1;
    dp[1] = 3;

    for (int i = 2; i < n; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2] * 2;
        dp[i] %= 10007;
    }

    std::cout << dp[n - 1] << "\n";

    return 0;
}