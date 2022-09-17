#include <cstdio>
#include <queue>

struct Point
{
	int x;
	int y;
	Point (int x, int y) : x(x), y(y)
	{
	}
};

int               n, m, q, k;
int               ans  (0);
const int         maxN (1000    + 10);
const int         maxK (1000000 + 10);
int               s    [maxN][maxN];
bool              in   [maxN][maxN];
int               xDir [4] = {1, 0, -1, 0};
int               yDir [4] = {0, 1, 0, -1};
std::queue<Point> queue[maxK];

bool can(const Point &p)
{
	return    p.x >= 1 && p.x <= n
	       && p.y >= 1 && p.y <= m
	       && !in[p.x][p.y];
}

void expand(int color)
{
	while (!queue[color].empty())
	{
		Point p(queue[color].front());
		queue[color].pop();
		++ans;

		for (int i(0); i < 4; ++i)
		{
			Point nxt(p.x + xDir[i], p.y + yDir[i]);
			if (can(nxt))
			{
				in[nxt.x][nxt.y] = true;
				queue[s[nxt.x][nxt.y]].push(nxt);
			}
		}
	}
	queue[color] = std::queue<Point>();
}

int main()
{
	//freopen("color.in", "r", stdin);
	//freopen("color.out", "w", stdout);

	scanf("%d %d %d %d", &n, &m, &q, &k);
	for (int i(1); i <= n; ++i)
	{
		for (int j(1); j <= m; ++j)
		{
			scanf("%d", &s[i][j]);
		}
	}
	in[1][1] = true;
	queue[s[1][1]].push(Point(1, 1));
	expand(s[1][1]);

	for (int qqq(1); qqq <= q; ++qqq)
	{
		int x;
		scanf("%d", &x);
		expand(x);
		printf("%d\n", ans);
	}

	return 0;
}
