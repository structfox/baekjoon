#include <iostream>

const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {1, -1, 0, 0};
const int MAX = 200;
char MAP[MAX][MAX];
int MAP_Time[MAX][MAX];

int main()
{
	int R, C, N;
	std::cin >> R >> C >> N;
	
	// 0 sec
	for (int i = 0; i < R; ++i)
	{
		std::string str;
		std::cin >> str;
		for (int j = 0; j < str.length(); ++j)
		{
			MAP[i][j] = str.at(j);
			MAP_Time[i][j] = 0;
		}
	}
	
	// 1 sec do nothing
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (MAP[i][j] == 'O') MAP_Time[i][j]++;
		}
	}
	
	// 2 sec
	for (int i = 2; i <= N; i++)
	{
		switch (i % 2)
		{
			case 0:
				for (int j = 0; j < R; j++)
				{
					for (int k = 0; k < C; k++)
					{
						if (MAP[j][k] == '.')
						{
							MAP[j][k] = 'O';
							MAP_Time[j][k] = 0;
						}
						else
						{
							MAP_Time[j][k]++;
						}
					}
				}
				break;
			case 1:
				for (int j = 0; j < R; j++)
				{
					for (int k = 0; k < C; k++)
					{
						if (MAP[j][k] == 'O') MAP_Time[j][k]++;
					}
				}
				
				for (int j = 0; j < R; j++)
				{
					for (int k = 0; k < C; k++)
					{
						if (MAP_Time[j][k] == 3)
						{
							MAP[j][k] = '.';
							for (int l = 0; l < 4; l++)
							{
								if (j + dr[l] < 0 || j + dr[l] >= R || k + dc[l] < 0 || k + dc[l] >= C) continue;
								
								MAP[j + dr[l]][k + dc[l]] = '.';
							}
						}
					}
				}
				break;
		}
	}
	
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			std::cout << MAP[i][j];
		}
		std::cout << "\n";
	}
	
	return 0;
}
