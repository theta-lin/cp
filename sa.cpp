#include <cstdio>
#include <cstring>
#include <algorithm>

int n;

const int maxN   (400000 + 10);
const int maxChar(26);
const int maxLbN (30);
char      S      [maxN];
int       sa     [maxN];
int       rank   [maxN];
int       cnt    [maxN];
int       second [maxN];
int       rankSec[maxN];
int       oldRank[maxN];
int       height [maxN];
int       st     [maxLbN][maxN];

void buildSa()
{
	int max(maxChar);
	memset(cnt + 1, 0, max * sizeof(int));
	for (int i(1); i <= n; ++i) ++cnt[rank[i] = int(S[i] - 'a' + 1)];
	for (int i(2); i <= max; ++i) cnt[i] += cnt[i - 1];
	for (int i(n); i >= 1; --i) sa[cnt[rank[i]]--] = i;

	for (int mid(1); mid < n; mid *= 2)
	{
		int front(0);
		for (int i(n - mid + 1); i <= n; ++i)
		{
			second[++front] = i;
		}
		for (int i(1); i <= n; ++i)
		{
			if (sa[i] >= mid + 1)
			{
				second[++front] = sa[i] - mid;
			}
		}

		memset(cnt + 1, 0, max * sizeof(int));
		for (int i(1); i <= n; ++i) ++cnt[rankSec[i] = rank[second[i]]];
		for (int i(2); i <= max; ++i) cnt[i] += cnt[i - 1];
		for (int i(n); i >= 1; --i) sa[cnt[rankSec[i]]--] = second[i];

		memcpy(oldRank + 1, rank + 1, n * sizeof(int));

		int id(0);
		for (int i(1); i <= n; ++i)
		{
			int x(sa[i - 1]), y(sa[i]);
			if (oldRank[x] != oldRank[y] || oldRank[x + mid] != oldRank[y + mid])
			{
				++id;
			}
			rank[y] = id;
		}

		max = id;
		if (max == n) break;
	}

	/*for (int i(1); i <= n; ++i)
    {
        printf("%d ", sa[i]);
    }
    printf("\n"); //*/
}

void calcHeight()
{
	for (int i(1); i <= n; ++i)
	{
		height[rank[i]] = std::max(height[rank[i - 1]] - 1, 0);
		while (S[i + height[rank[i]]] == S[sa[rank[i] - 1] + height[rank[i]]])
		{
			++height[rank[i]];
		}
	}

	for (int i(1); i <= n; ++i)
	{
		st[0][i] = height[i];
	}
	for (int i(1); i < maxLbN; ++i)
	{
		for (int j(1); j + (1 << i) - 1 <= n; ++j)
		{
			st[i][j] = std::min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
		}
	}
}

int lb(int x)
{
	int y(0);
	while ((1 << y) <= x)
	{
		++y;
	}
	return y - 1;
}

int get(int x, int y)
{
	x = rank[x];
	y = rank[y];
	if (x > y) std::swap(x, y);
	++x;
	int l(lb(y - x + 1));
	return std::min(st[l][x], st[l][y - (1 << l) + 1]);
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int ttt(1); ttt <= T; ++ttt)
	{
		scanf("%s", S + 1);
		n = strlen(S + 1);

		buildSa();
		calcHeight();

		/*for (int i(1); i <= n; ++i)
		{
			printf("height %d: %d\n", i, height[i]);
		}//*/
		/*for (int i(1); i <= n; ++i)
		{
			for (int j(i); j <= n; ++j)
			{
				printf("min [%d,%d]: %d\n", i, j, get(i, j));
			}
		}//*/

		int ansPos(sa[1]), ansCnt(1), ansLen(1);
		for (int i(1); i <= n / 2; ++i)
		{
			for (int j(1); j + i <= n; j += i)
			{
				int len(get(j, j + i));
				if (len / i + 1 + 1 >= ansCnt)
				{
					//printf("%d %d @@ $%d %s\n", i, j, len, S + j);
					for (int k(j); k >= 1 && j - k < i && S[k] == S[k + i]; --k)
					{
	  					//printf("%d %d %d $%d %s\n", i, j, k, len, S + k);
						if (len / i + 1 > ansCnt || (len / i + 1 == ansCnt && rank[k] < rank[ansPos]))
						{
							ansPos = k;
							ansCnt = len / i + 1;
							ansLen = i;
						}
						++len;
					}
				}
			}
		}

		for (int i(0); i < ansCnt * ansLen; ++i)
		{
			putchar(S[ansPos + i]);
		}
		puts("");
	}

	return 0;
}
