// 5093

#include <cstdio>
#include <vector>
#include <cctype>

struct Event
{
	int x1;
	int y1;
	int x2;
	int y2;
	int k;
};

const int len(4000000);
int n, m, T;
class Array
{
private:
	int data[len];
public:
	int& operator()(int x, int y)
	{
		return data[x * m + y];
	}
};

Array a;
Array map;
Array killed;
Array delta;
Event event[len];
int mapK[len];

int read()
{
	char ch(0);
	while (!isdigit(ch))
	{
		ch = getchar();
	}
	int x(0);
	while (isdigit(ch))
	{
		x = x * 10 + int(ch - '0');
		ch = getchar();
	}
	return x;
}

void kill(int color)
{
	for (int i(1); i <= n; ++i)
	{
		for (int j(1); j <= m; ++j)
		{
			delta(i, j) = 0;
		}
	}
	for (int i(1); i <= T; ++i)
	{
		if (mapK[i] == color)
		{
			++delta(event[i].x1, event[i].y1);
			--delta(event[i].x1, event[i].y2 + 1);
			--delta(event[i].x2 + 1, event[i].y1);
			++delta(event[i].x2 + 1, event[i].y2 + 1);
		}
	}
	for (int i(1); i <= n; ++i)
	{
		for (int j(1); j <= m; ++j)
		{
			//printf("%d ", delta[i][j]);
			delta(i, j) += delta(i - 1, j) + delta(i, j - 1) - delta(i - 1, j - 1);

			if (map(i ,j) != color && delta(i, j))
			{
				killed(i, j) = true;
			}
		}
		//printf("\n");
	}
	//printf("\n");
}

int main()
{
	n = read(); m = read(); T = read();
	for (int i(1); i <= n; ++i)
	{
		for (int j(1); j <= m; ++j)
		{
			a(i, j) = read();
		}
	}
	for (int i(1); i <= T; ++i)
	{
		event[i].x1 = read();
		event[i].y1 = read();
		event[i].x2 = read();
		event[i].y2 = read();
		event[i].k = read();
	}

	for (int digit(0); digit < 25; ++digit)
	{
		for (int i(1); i <= n; ++i)
		{
			for (int j(1); j <= m; ++j)
			{
				map(i, j) = (a(i, j) >> digit & 1);
			}
		}

		for (int i(1); i <= T; ++i)
		{
			mapK[i] = (event[i].k >> digit & 1);
		}

		kill(0);
		kill(1);
	}

	int ans(0);
	for (int i(1); i <= n; ++i)
	{
		for (int j(1); j <= m; ++j)
		{
			ans += killed(i, j);
		}
	}
	printf("%d\n", ans);
	return 0;
}
