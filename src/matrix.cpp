#include <iostream>

int N, T;
int map[9 * 10 + 10][9 * 10 + 10];
int ans[9 * 10 + 10][9 * 10 + 10];
int tmp[9 * 10 + 10][9 * 10 + 10];
const int mod(2009);

void mult(int a[9 * 10 + 10][9 * 10 + 10], int b[9 * 10 + 10][9 * 10 + 10], int c[9 * 10 + 10][9 * 10 + 10])
{
	for (int i(1); i <= N * 9; ++i)
	{
		for (int j(1); j <= N * 9; ++j)
		{
			tmp[i][j] = 0;
			for (int k(1); k <= N * 9; ++k)
			{
				tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % mod;
			}
		}
	}

	for (int i(1); i <= N * 9; ++i)
		for (int j(1); j <= N * 9; ++j)
			c[i][j] = tmp[i][j];
}

int main()
{
	std::cin >> N >> T;
	for (int i(0); i < N; ++i)
	{
		for (int j(0); j < N; ++j)
		{
			char ch;
			std::cin >> ch;
			int cost(static_cast<int>(ch - '0'));
			if (cost != 0)
			{
				for (int k(1); k <= cost - 1; ++k)
					map[i * 9 + k][i * 9 + k + 1] = 1;
				map[i * 9 + cost][j * 9 + 1] = 1;
			}
		}
	}

	for (int i(1); i <= N * 9; ++i)
		ans[i][i] = 1;

	for (int i(1); i <= T; i <<= 1)
	{
		if (i & T)
			mult(ans, map, ans);
		mult(map, map, map);

		/*for (int ii(1); ii <= N * 9; ++ii)
		{
			for (int j(1); j <= N * 9; ++j)
			{
				std::cout << map[ii][j] << ' ';
			}
			std::cout << std::endl;
		}*/
		//std::cout << i << ' ' << T << std::endl;
		//system("pause");
	}

	std::cout << ans[0 * 9 + 1][(N - 1) * 9 + 1] << std::endl;
	return 0;
}
