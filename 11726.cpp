#include <iostream>

int main()
{
    int dp[1000];
    dp[0] = 1;
    dp[1] = 2;

    int n;
    std::cin >> n;
    for (int i = 2; i < n; i++)
    {
        dp[i] = dp[i - 2] + dp[i - 1];
        dp[i] %= 10007;
    }
    
    std::cout << dp[n - 1];

    return 0;
}