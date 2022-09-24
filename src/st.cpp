#include <algorithm>

const int maxN  (1000000);
const int maxLbN(20);

int a [maxN];
int lb[maxN];
int f [maxLbN][maxN];

int n;

int query(int l, int r)
{
	int lbLen(lb[r - l + 1]);
	return std::max(f[lbLen][l], f[lbLen][r - (1 << lbLen) + 1]);
}

void init()
{
	lb[0] = -1;
	for (int i(1); i <= n; ++i)
	{
		lb[i] = lb[i / 2] + 1;
	}

	for (int i(1); i <= n; ++i)
	{
		f[0][i] = a[i];
	}
	for (int i(1); i < maxLbN; ++i)
	{
		for (int j(1); j + (1 << i) - 1 <= n; ++j)
		{
			f[i][j] = std::max(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
		}
	}
}
