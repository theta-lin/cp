// 5074

#include <cstdio>
#include <algorithm>

int       n, m;
int       ans;
const int maxN    (1000000 + 10);
const int maxLbN  (30);
const int maxM    (100000 + 10);
int       color   [maxN];
int       to      [maxN * 2];
int       pre     [maxN * 2];
int       last    [maxN];
int       jump    [maxN][maxLbN];
int       depth   [maxN];
int       max     [maxN];
int       sMax    [maxN];
int       colFirst[maxM];
int       colLast [maxM];
int       cnt     [maxN];
bool      dom     [maxN];

void addEdge(int u, int v)
{
	static int lastEdge(0);
	++lastEdge;
	to[lastEdge] = v;
	pre[lastEdge] = last[u];
	last[u] = lastEdge;
}

void prep(int v, int pred)
{
	depth[v] = depth[pred] + 1;
	jump[v][0] = pred;
	for (int i(1); i < maxLbN; ++i)
	{
		jump[v][i] = jump[jump[v][i - 1]][i - 1];
	}

	for (int e(last[v]); e; e = pre[e])
	{
		if (to[e] != pred)
		{
			prep(to[e], v);

			if (max[to[e]] + 1 > max[v])
			{
				sMax[v] = max[v];
				max[v] = max[to[e]] + 1;
			}
			else if (max[to[e]] + 1 > sMax[v])
			{
				sMax[v] = max[to[e]] + 1;
			}
		}
	}
}

int lca(int l, int h)
{
	if (depth[l] < depth[h]) std::swap(l, h);

	for (int i(maxLbN - 1); i >= 0; --i)
	{
		if (depth[jump[l][i]] >= depth[h])
		{
			l = jump[l][i];
		}
	}

	if (l == h) return l;

	for (int i(maxLbN - 1); i >= 0; --i)
	{
		if (jump[l][i] != jump[h][i])
		{
			l = jump[l][i];
			h = jump[h][i];
		}
	}

	return jump[l][0];
}

void count(int v, int pred)
{
	++cnt[v];
	if (!colFirst[color[v]])
	{
		colFirst[color[v]] = v;
	}
	else
	{
		--cnt[lca(colLast[color[v]], v)];
	}
	colLast[color[v]] = v;

	for (int e(last[v]); e; e = pre[e])
	{
		if (to[e] != pred)
		{
			count(to[e], v);
		}
	}
}

void solve(int v, int pred, int outDep)
{
	for (int e(last[v]); e; e = pre[e])
	{
		if (to[e] != pred)
		{
			int curMax(max[to[e]] + 1 == max[v] ? sMax[v] : max[v]);
			solve(to[e], v, std::max(curMax, outDep) + 1);
			cnt[v] += cnt[to[e]];
			dom[v] = (dom[v] || dom[to[e]]);
		}
	}

	if (cnt[v] == m) ans = std::max(ans, outDep + 1);
	if (!dom[v]) ans = std::max(ans, max[v] + 2);
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int v(1); v <= n; ++v)
	{
		scanf("%d", &color[v]);
	}
	for (int e(1); e <= n - 1; ++e)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}

	prep(1, 0);
	count(1, 0);
	for (int i(1); i <= m; ++i)
	{
		dom[lca(colFirst[i], colLast[i])] = true;
	}

	solve(1, 0, 0);
	printf("%d\n", ans);
	return 0;
}
