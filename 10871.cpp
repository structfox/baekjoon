#include <iostream>

int arr_in[10000];
int arr_out[10000];
int num = 0;
int n;
int x;

void sel()
{
    for (int i = 0; i < n; ++i)
    {
        if (arr_in[i] < x)
            arr_out[num] = arr_in[i];
            ++num;
    }
}

int main()
{
    std::cin >> n >> x;
    for (int i = 0; i < n; ++i)
        std::cin >> arr_in[i];
    
    sel();
    
    for (int i = 0; i < num; ++i)
        std::cout << arr_out[i] << " ";
        
    return 0;
}
