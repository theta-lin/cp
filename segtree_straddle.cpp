// 5276

#include <cstdio>
#include <algorithm>
#include <deque>

const int maxN(2000 + 10);
char      in  [maxN];
int       max [maxN];
int       lMin[maxN][maxN];
int       rMin[maxN][maxN];

int n, m, k;

void init(int tl, int tr)
{
	if (tl > tr) return;

	int mid((tl + tr) / 2);
	max[mid] = std::max(mid - tl + 1, tr - mid);
	for (int y(1); y <= m; ++y)
	{
		lMin[mid][y] = mid - tl + 1;
		rMin[mid][y] = tr - mid;
	}

	if (tl < tr)
	{
		init(tl, mid - 1);
		init(mid + 1, tr);
	}
}

void update(int tl, int tr, int x, int y)
{
	if (tl > tr) return;

	int mid((tl + tr) / 2);
	if (x == mid)
	{
		lMin[mid][y] = rMin[mid][y] = 0;
	}
	else if (x < mid)
	{
		lMin[mid][y] = std::min(lMin[mid][y], mid - x);
	}
	else
	{
		rMin[mid][y] = std::min(rMin[mid][y], x - mid - 1);
	}

	max[mid] = 0;
	if (x < mid)
	{
		update(tl, mid - 1, x, y);

	}
	else if (x > mid)
	{
		update(mid + 1, tr, x, y);
	}

	max[mid] = 0;
	if (tl <= mid - 1)
	{
		max[mid] = std::max(max[mid], max[(tl + mid - 1) / 2]);
	}
	if (mid + 1 <= tr)
	{
		max[mid] = std::max(max[mid], max[(mid + 1 + tr) / 2]);
	}

//	printf("update: [%d,%d]\n", tl, tr);

	std::deque<int> lQueue, rQueue;
	for (int l(1), r(1); r <= m; ++r)
	{
		while (!lQueue.empty() && lMin[mid][r] <= lMin[mid][lQueue.back()])
		{
			lQueue.pop_back();
		}
		lQueue.push_back(r);

		while (!rQueue.empty() && rMin[mid][r] <= rMin[mid][rQueue.back()])
		{
			rQueue.pop_back();
		}
		rQueue.push_back(r);

//		printf("(%d,%d)", lQueue.front(), rQueue.front());
		while (!lQueue.empty() && !rQueue.empty() && r - l + 1 > lMin[mid][lQueue.front()] + rMin[mid][rQueue.front()])
		{
			++l;
			if (l > lQueue.front()) lQueue.pop_front();
			if (l > rQueue.front()) rQueue.pop_front();
		}
//		printf("[%d,%d] ", l, r);
		max[mid] = std::max(max[mid], r - l + 1);
	}
//	printf("\n");
}

void print(int tl, int tr)
{
	if (tl > tr) return;

	printf("[%d,%d]\n", tl, tr);
	int mid((tl + tr) / 2);
	for (int x(1); x <= n; ++x)
	{
		for (int y(1); y <= m; ++y)
		{
			if (x <= mid)
			{
				if (mid - x + 1 <= lMin[mid][y])
				{
					printf("L");
				}
				else
				{
					printf(".");
				}
			}
			else
			{
				if (x - mid <= rMin[mid][y])
				{
					printf("R");
				}
				else
				{
					printf(".");
				}
			}
		}
		printf("\n");
	}

	if (tl < tr)
	{
		print(tl, mid - 1);
		print(mid + 1, tr);
	}
}

int main()
{
	scanf("%d %d %d", &n, &m, &k);
	init(1, n);
	for (int x(1); x <= n; ++x)
	{
		scanf("%s", in + 1);
		for (int y(1); y <= m; ++y)
		{
			if (in[y] == 'X')
			{
				update(1, n, x, y);
			}
		}
	}
	//print(1, n);

	for (int qqq(1); qqq <= k; ++qqq)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		update(1, n, x, y);
		printf("%d\n", max[(1 + n) / 2]);
	}

	return 0;
}
