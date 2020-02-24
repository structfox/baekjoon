#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int N, B, C;
    int sum = 0;
    std::vector<double> app;

    std::cin >> N;
    for (int i = 0; i <  N; ++i)
    {
        double A;
        std::cin >> A;
        app.push_back(A);
    }
    std::cin >> B >> C;

    for (int i = 0; i < N; ++i)
    {
        app[i] -= B;
        if (app[i] > 0)
            sum += std::ceil(app[i] / C);
    }

    sum += N;

    std::cout << sum;
    return 0;
}