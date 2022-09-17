// 5192

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <utility>

struct Query
{
	int x;
	int v;
};

const int              maxN       (2 * 100000 + 10);
int                    n, q;
int                    orderedSize;
int                    crit;
long long              ans;
int                    a          [maxN];
int                    cur        [maxN];
long long              ordered    [maxN];
int                    degree     [maxN];
Query                  query      [maxN];
std::vector<int>       edge       [maxN];
std::vector<int>       large      [maxN];
std::vector<int>       bitCnt     [maxN];
std::vector<long long> bitVal     [maxN];

int myLog2(int x)
{
	int cur(1), result(0);
	while (cur < x)
	{
		cur *= 2;
		++result;
	}
	return result;
}

int getIndex(long long value)
{
	return std::lower_bound(ordered + 1, ordered + orderedSize + 1, value) - ordered;
}

int lowbit(int x)
{
	return x & (-x);
}

void add(int id, int pos, int cnt, long long value)
{
	if (pos == 0) return;

	while (pos <= orderedSize)
	{
		bitCnt[id][pos] += cnt;
		bitVal[id][pos] += value;
		pos += lowbit(pos);
	}
}

long long queryCnt(int id, int pos)
{
	long long sum(0);
	while (pos > 0)
	{
		sum += bitCnt[id][pos];
		pos -= lowbit(pos);
	}
	return sum;
}

long long queryVal(int id, int pos)
{
	long long sum(0);
	while (pos > 0)
	{
		sum += bitVal[id][pos];
		pos -= lowbit(pos);
	}
	return sum;
}

long long calc(int v)
{
	long long sum(0);
	if (degree[v] <= crit)
	{
		for (std::size_t e(0); e < edge[v].size(); ++e)
		{
			int to(edge[v][e]);
			sum += std::min(ordered[cur[v]], ordered[cur[to]]);
		}
	}
	else
	{
		sum += (queryCnt(v, orderedSize) - queryCnt(v, cur[v])) * ordered[cur[v]];
		sum += queryVal(v, cur[v]);
	}

	return sum;
}

void update(int v, int value)
{
	//printf("update: %d with %lld\n", v, ordered[cur[v]]);

	//printf("erase: %lld %lld\n", -ordered[cur[v]], calc(v));

	ans -= ordered[cur[v]];
	ans += calc(v);

	for (std::size_t e(0); e < large[v].size(); ++e)
	{
		int to(large[v][e]);
		add(to, cur[v], -1, -ordered[cur[v]]);
		add(to, value, 1, ordered[value]);
	}
	cur[v] = value;

	//printf("add: %lld %lld\n", ordered[cur[v]], -calc(v));

	ans += ordered[cur[v]];
	ans -= calc(v);
}

int main()
{
//	freopen("sorry.in", "r", stdin);
//	freopen("sorry.out", "w", stdout);

	scanf("%d %d", &n, &q);
	for (int v(1); v <= n; ++v)
	{
		scanf("%d", &a[v]);
		ordered[++orderedSize] = a[v];
	}
	for (int e(1); e <= n - 1; ++e)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		edge[u].push_back(v);
		edge[v].push_back(u);
		++degree[u];
		++degree[v];
	}
	for (int qqq(1); qqq <= q; ++qqq)
	{
		scanf("%d %d", &query[qqq].x, &query[qqq].v);
		ordered[++orderedSize] = query[qqq].v;
	}

	std::sort(ordered + 1, ordered + orderedSize + 1);
	orderedSize = std::unique(ordered + 1, ordered + orderedSize + 1) - ordered - 1;
	for (int v(1); v <= n; ++v)
	{
		a[v] = getIndex(a[v]);
	}
	for (int qqq(1); qqq <= q; ++qqq)
	{
		query[qqq].v = getIndex(query[qqq].v);
	}

	crit = sqrt(2 * (n - 1) * myLog2(orderedSize));
	for (int v(1); v <= n; ++v)
	{
		for (std::size_t e(0); e < edge[v].size(); ++e)
		{
			int to(edge[v][e]);
			if (degree[to] > crit)
			{
				large[v].push_back(to);
			}
		}
	}
	for (int v(1); v <= n; ++v)
	{
		if (degree[v] > crit)
		{
			bitCnt[v].resize(orderedSize + 1);
			bitVal[v].resize(orderedSize + 1);
		}
	}

	for (int v(1); v <= n; ++v)
	{
		update(v, a[v]);
	}

	for (int qqq(1); qqq <= q; ++qqq)
	{
		update(query[qqq].x, query[qqq].v);
		printf("%lld\n", ans);
	}
	return 0;
}
