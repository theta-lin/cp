// 5274

#include <cstdio>
#include <limits>
#include <algorithm>
#include <cstring>

const int maxN(100 + 10);
int       a   [maxN];
int       f   [maxN][maxN][maxN];

void solve(int l, int r, int k, int zero)
{
	memset(f[l][r], 0, sizeof(f[l][r]));
	if (l > r) return;

	int min(l);
	for (int i(l); i <= r; ++i)
	{
		if (a[i] < a[min])
		{
			min = i;
		}
	}

	solve(l, min - 1, k, zero);
	solve(min + 1, r, k, zero);
	for (int i(1); i <= k; ++i)
	{
		for (int j(0); j <= i; ++j)
		{
			f[l][r][i] = std::max(f[l][r][i], f[l][min - 1][j] + f[min + 1][r][i - j]);
		}
	}

	/*printf("[%d,%d] %d: ", l, r, zero);
	for (int i(1); i <= k; ++i)
	{
		printf("%d ", f[l][r][i]);
	}
	printf("\n"); //*/

	solve(l, min - 1, k, a[min]);
	solve(min + 1, r, k, a[min]);
	for (int i(1); i <= k; ++i)
	{
		for (int j(0); j <= i - 1; ++j)
		{
			f[l][r][i] = std::max(f[l][r][i], f[l][min - 1][j] + f[min + 1][r][i - j - 1] + (r - l + 1) * (a[min] - zero));
		}
	}

	/*printf("[%d,%d] %d: ", l, r, zero);
	for (int i(1); i <= k; ++i)
	{
		printf("%d ", f[l][r][i]);
	}
	printf("\n"); //*/
}

int main()
{
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i(1); i <= n; ++i)
	{
		scanf("%d", &a[i]);
	}

	solve(1, n, k, 0);
	printf("%d\n", f[1][n][k]);
	return 0;
}
