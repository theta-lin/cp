// 5128

#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

const int maxN (12);
char      in   [maxN];
int       color[maxN][maxN];
int       w    [maxN][maxN];
int       dp   [1 << (2 * maxN)];
int       n;

struct Point
{
	int pos;
	int x;
	int y;
};

void print(int x)
{
	for (int i(0); i < 2 * n; ++i)
	{
		printf("%d", (x >> i) & 1);
	}
	printf("\n");
}

int main()
{
	scanf("%d", &n);
	for (int i(0); i < n; ++i)
	{
		scanf("%s", in);
		for (int j(0); j < n; ++j)
		{
			if (in[j] == 'W')
			{
				color[i][j] = 1;
			}
			else if (in[j] == 'B')
			{
				color[i][j] = 2;
			}
			else
			{
				color[i][j] = 0;
			}
		}
	}
	for (int i(0); i < n; ++i)
	{
		for (int j(0); j < n; ++j)
		{
			scanf("%d", &w[i][j]);
		}
	}

	const int inf(0x3f3f3f3f);
	memset(dp, inf, sizeof(dp));
	dp[(1 << (2 * n)) - (1 << n)] = 0;

	for (int state(1 << (2 * n)); state; --state)
	{
		if (dp[state] != inf)
		{
			std::vector<Point> corner;
			{
				Point p = {0, -1, 0};
				while(p.pos < 2 * n - 1)
				{
					p.x += (((state >> p.pos) & 1) == 0);
					p.y += (((state >> p.pos) & 1) == 1);
					if (0 <= p.x && p.x < n && 0 <= p.y && p.y < n && ((state >> p.pos) & 3) == 2)
					{
						corner.push_back(p);
					}
					++p.pos;
				}
			}

			for (std::size_t i(0); i < corner.size(); ++i)
			{
				int nxt(state ^ (3 << corner[i].pos));
				dp[nxt] = std::min(dp[nxt], dp[state] + w[corner[i].x][corner[i].y]);
			}

			for (std::size_t i(0); i < corner.size(); ++i)
			{
				if (color[corner[i].x][corner[i].y])
				{
					for (std::size_t j(0); j < corner.size(); ++j)
					{
						if (color[corner[j].x][corner[j].y] && color[corner[i].x][corner[i].y] != color[corner[j].x][corner[j].y])
						{
							int nxt(state ^ (3 << corner[i].pos) ^ (3 << corner[j].pos));
							dp[nxt] = std::min(dp[nxt], dp[state] + std::abs(w[corner[i].x][corner[i].y] - w[corner[j].x][corner[j].y]));
						}
					}
				}
			}
		}
	}

	printf("%d\n", dp[(1 << n) - 1]);
	return 0;
}
