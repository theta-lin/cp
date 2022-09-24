// 4343

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cctype>
#include <iostream>

struct Question
{
	int type;
	int l;
	int r;
	long long v;
};

const int maxN (200000 + 10);
long long a    [maxN];
long long delta[maxN];
long long data [maxN];
Question  quest[maxN];

int n;
int size;

long long read()
{
	char ch(0), sign(0);
	do
	{
		sign = ch;
		ch = getchar();
	}
	while (!isdigit(ch));
	long long x(0);
	while (isdigit(ch))
	{
		x = x * 10 + int(ch - '0');
		ch = getchar();
	}
	return sign == '-' ? -x : x;
}

double cnt1, cnt2;
double sum1, sum2;

double f(double x)
{
	return 5 * cnt1 * x * std::max(std::log(x) / std::log(2), 1.0) + sum1 / x + 5 * cnt2  * x + sum2 / x * std::max(std::log(x) / std::log(2), 1.0);
}

void getSize()
{
	size = 1;
	for (int i(2); i <= n; ++i)
	{
		if (f(i) < f(size))
		{
			size = i;
		}
	}
}

void rebuild(int block)
{
	for (int i(block * size); i <= n && i / size == block; ++i)
	{
		data[i] = a[i];
	}
	std::sort(&data[block * size], &data[(block + 1) * size]);
}

void add(int l, int r, long long v)
{
	int blkBeg(l / size), blkEnd(r / size);
	for (int i(l); i <= r && i / size == blkBeg; ++i)
	{
		a[i] += v;
	}
	rebuild(blkBeg);

	if (blkBeg < blkEnd)
	{
		for (int i(r); i >= l && i / size == blkEnd; --i)
		{
			a[i] += v;
		}
		rebuild(blkEnd);
	}
	for (int block(blkBeg + 1); block <= blkEnd - 1; ++block)
	{
		delta[block] += v;
	}
}

int query(int l, int r, long long k)
{
	int ans(0);
	int blkBeg(l / size), blkEnd(r / size);

	for (int i(l); i <= r && i / size == blkBeg; ++i)
	{
		if (delta[blkBeg] + a[i] <= k)
		{
			++ans;
		}
	}
	if (blkBeg < blkEnd)
	{
		for (int i(r); i >= l && i / size == blkEnd; --i)
		{
			if (delta[blkEnd] + a[i] <= k)
			{
				++ans;
			}
		}
	}

	for (int block(blkBeg + 1); block <= blkEnd - 1; ++block)
	{
		ans += std::upper_bound(&data[block * size], &data[(block + 1) * size], k - delta[block]) - &data[block * size];
	}
	return ans;
}

int main()
{
	//freopen("ds.in", "r", stdin);
	//freopen("ds.out", "w", stdout);

	n = read();
	for (int i(0); i < n; ++i)
	{
		a[i] = read();
	}

	int m(read());
	for (int qqq(1); qqq <= m; ++qqq)
	{
		quest[qqq].type = read();
		quest[qqq].l = read();
		quest[qqq].r = read();
		quest[qqq].v = read();
		if (quest[qqq].type == 1)
		{
			++cnt1;
			sum1 += quest[qqq].r - quest[qqq].l + 1;
		}
		else
		{
			++cnt2;
			sum2 += quest[qqq].r - quest[qqq].l + 1;
		}
	}

	getSize();

	std::cerr << size << '\n';

	for (int i(0); i <= (n - 1) / size; ++i)
	{
		rebuild(i);
	}

	for (int qqq(1); qqq <= m; ++qqq)
	{
		if (quest[qqq].type == 1)
		{
			add(quest[qqq].l - 1, quest[qqq].r - 1, quest[qqq].v);
		}
		else
		{
			printf("%d\n", query(quest[qqq].l - 1, quest[qqq].r - 1, quest[qqq].v));
		}
	}
	return 0;
}
