#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false); 
    
    int num;
    std::cin >> num;
    
    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < num - i - 1; ++j)
            std::cout << " ";
        
        for (int j = 0; j < 2 * (i+1) - 1; ++j)
            std::cout << "*";
        
        std::cout << "\n";
    }
    return 0;
}
