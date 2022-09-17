#include <cstdio>
#include <algorithm>

struct Interval
{
	int l;
	int r;
	int len;

	Interval() : l(0), r(0)
	{
	}

	Interval(int l, int r) : l(l), r(r)
	{
	}

	int mid() const
	{
		return (l + r) / 2;
	}
};

int *end;
const int maxN(524288 + 10);
Interval inter [maxN];
int      lookup[maxN * 2 * 2];
int      max   [maxN * 2 * 2];
int      delta [maxN * 2 * 2];

bool operator<(const Interval &a, const Interval &b)
{
	return a.len < b.len;
}

int get(int x)
{
	return std::lower_bound(lookup, end, x) - lookup + 1;
}

void modify(int node, const Interval &cur, const Interval &op, int value)
{
	if (cur.l >= op.l && cur.r <= op.r)
	{
		delta[node] += value;
		max[node] += value;
		return;
	}
	else
	{
		if (op.l <= cur.mid()) modify(node * 2, Interval(cur.l, cur.mid()), op, value);
		if (op.r >= cur.mid() + 1) modify(node * 2 + 1, Interval(cur.mid() + 1, cur.r), op, value);
	}
	max[node] = std::max(max[node * 2], max[node * 2 + 1]) + delta[node];
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i(1); i <= n; ++i)
	{
		scanf("%d %d", &inter[i].l, &inter[i].r);
		inter[i].len = inter[i].r - inter[i].l + 1;
		lookup[i * 2 - 1] = inter[i].l;
		lookup[i * 2] = inter[i].r;
	}

	std::sort(inter + 1, inter + n + 1);
	std::sort(lookup + 1, lookup + n * 2 + 1);
	end = std::unique(lookup + 1, lookup + n * 2 + 1);
	int limit(0);
	for (int i(1); i <= n; ++i)
	{
		inter[i].l = get(inter[i].l);
		inter[i].r = get(inter[i].r);
		limit = std::max(limit, inter[i].r);
	}

	int ans(0x7fffffff);
	for (int r(1), l(1); r <= n; ++r)
	{
		modify(1, Interval(1, limit), inter[r], 1);
		while (max[1] >= m && l <= r)
		{
			ans = std::min(ans, inter[r].len - inter[l].len);
			modify(1, Interval(1, limit), inter[l], -1);
			++l;
		}
	}
	printf("%d\n", ans == 0x7fffffff ? -1 : ans);
	return 0;
}
