#include <iostream>
#include <cstring>
#include <algorithm>

long long n, m;
const long long inf(0x7f7f7f7f);

struct Edge
{
	long long from;
	long long to;
	long long cost;
};
Edge edge  [300000     + 10];
bool inMst [300000     + 10];
long long  father[100000     + 10];

long long  to    [300000 * 2 + 10];
long long  pre   [300000 * 2 + 10];
long long  last  [100000     + 10];
long long  cost  [300000 * 2 + 10];

long long  depth [100000     + 10];
long long  lca   [100000     + 10][20];
long long  max1  [100000     + 10][20];
long long  max2  [100000     + 10][20];

bool operator<(const Edge &a, const Edge &b)
{
	return a.cost < b.cost;
}

void addEdge(long long x, long long y, long long z)
{
	static long long index(0);
	to[index] = y;
	pre[index] = last[x];
	last[x] = index;
	cost[index] = z;
	++index;
}

long long getFather(long long vertex)
{
	if (father[vertex] == vertex)
		return vertex;
	else
		return father[vertex] = getFather(father[vertex]);
}

long long kruskal()
{
	for (long long i(1); i <= n; ++i)
		father[i] = i;
	std::sort(edge + 1, edge + m + 1);
	long long sum(0);
	for (long long i(1); i <= m; ++i)
	{
		long long fatherA(getFather(edge[i].from));
		long long fatherB(getFather(edge[i].to));
		if (fatherA != fatherB)
		{
			inMst[i] = true;
			sum += edge[i].cost;
			father[fatherA] = fatherB;
			addEdge(edge[i].from, edge[i].to, edge[i].cost);
			addEdge(edge[i].to, edge[i].from, edge[i].cost);
		}
	}

	return sum;
}

void dfs(long long vertex, long long pred, long long d)
{
	depth[vertex] = d;
	lca[vertex][0] = pred;
	for (long long i(last[vertex]); i != -1; i = pre[i])
	{
		if (to[i] != pred)
		{
			max1[to[i]][0] = cost[i];
			max2[to[i]][0] = -inf;
			dfs(to[i], vertex, d + 1);
		}
	}
}

long long getLca(long long v1, long long v2)
{
	if (depth[v1] < depth[v2])
		std::swap(v1, v2);
	for (long long i(19); i >= 0; --i)
	{
		if (depth[v1] - (1 << i) >= depth[v2])
			v1 = lca[v1][i];
	}
	if (v1 == v2)
		return v1;
	for (long long i(19); i >= 0; --i)
	{
		if (lca[v1][i] != lca[v2][i])
		{
			v1 = lca[v1][i];
			v2 = lca[v2][i];
		}
	}
	return lca[v1][0];
}

long long calc(long long v, long long f, long long replace)
{
	long long m1(-inf), m2(-inf);
	for (long long i(19); i >= 0; --i)
	{
		if (depth[v] - (1 << i) >= depth[f])
		{
			if (max1[v][i] > m1)
			{
				m2 = m1;
				m1 = max1[v][i];
			}
			m2 = std::max(m2, max2[v][i]);
			v = lca[v][i];
		}
	}

	if (m1 == replace)
		return replace - m2;
	else
		return replace - m1;
}

int main()
{
	std::cin >> n >> m;
	memset(last, -1, sizeof(last));
	for (long long i(1); i <= m; ++i)
		std::cin >> edge[i].from >> edge[i].to >> edge[i].cost;

	long long sum(kruskal());

	dfs(to[0], 0, 0);
	for (long long i(1); (1 << i) <= n; ++i)
	{
		for (long long j(1); j <= n; ++j)
		{
			lca[j][i] = lca[lca[j][i - 1]][i - 1];
			max1[j][i] = std::max(max1[j][i - 1], max1[lca[j][i - 1]][i - 1]);
			if (max1[j][i - 1] == max1[lca[j][i - 1]][i - 1])
				max2[j][i] = std::max(max2[j][i - 1], max2[lca[j][i - 1]][i - 1]);
			else if (max1[j][i - 1] < max1[lca[j][i - 1]][i - 1])
				max2[j][i] = std::max(max1[j][i - 1], max2[lca[j][i - 1]][i - 1]);
			else
				max2[j][i] = std::max(max2[j][i - 1], max1[lca[j][i - 1]][i - 1]);
		}
	}

	long long ans(inf);
	for (long long i(1); i <= m; ++i)
	{
		if (!inMst[i])
		{
			long long f(getLca(edge[i].from, edge[i].to));
			ans = std::min(ans, calc(edge[i].from, f, edge[i].cost));
			ans = std::min(ans, calc(edge[i].to, f, edge[i].cost));
		}
	}
	std::cout << sum + ans << std::endl;

	return 0;
}
