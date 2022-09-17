#include <cstdio>
#include <algorithm>
#include <vector>
#include <limits>

const int        maxN    (100000 + 10);
const int        logW    (30);
int              lastNode(0);
int              to      [maxN * 2];
int              pre     [maxN * 2];
int              weight  [maxN * 2];
int              last    [maxN];
int              sum     [maxN];
int              son     [maxN * logW][2];
std::vector<int> sub     [maxN * logW];

void addEdge(int x, int y, int w)
{
	static int lastEdge(0);
	++lastEdge;
	to[lastEdge] = y;
	pre[lastEdge] = last[x];
	weight[lastEdge] = w;
	last[x] = lastEdge;
}

void dfs(int v, int pred)
{
	for (int e(last[v]); e; e = pre[e])
	{
		if (to[e] != pred)
		{
			sum[to[e]] = sum[v] ^ weight[e];
			dfs(to[e], v);
		}
	}
}

void insert(int value)
{
	int node(0);
	for (int i(logW); i >= 0; --i)
	{
		int bit(value >> i & 1);
		if (!son[node][bit]) son[node][bit] = ++lastNode;
		node = son[node][bit];
		sub[node].push_back(value);
	}
}

int find(int node, int pos, int value)
{
	int delta(0);
	for (int i(pos); i >= 0; --i)
	{
		int bit(value >> i & 1);
		if (son[node][bit])
		{
			node = son[node][bit];
		}
		else
		{
			delta |= 1 << i;
			node = son[node][bit ^ 1];
		}
	}
	return delta;
}

long long solve(int node, int pos)
{
	long long ans(0);
	int l(son[node][0]), r(son[node][1]);
	if (l && r)
	{
		if (sub[l].size() > sub[r].size()) std::swap(l, r);
		int min(std::numeric_limits<int>::max());
		for (std::size_t i(0); i < sub[l].size(); ++i)
		{
			min = std::min(min, (1 << pos) | find(r, pos - 1, sub[l][i]));
		}
		ans += min;
	}

	if (l) ans += solve(l, pos - 1);
	if (r) ans += solve(r, pos - 1);
	return ans;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i(1); i <= n - 1; ++i)
	{
		int x, y;
		int w;
		scanf("%d %d %d", &x, &y, &w);
		++x, ++y;
		addEdge(x, y, w);
		addEdge(y, x, w);
	}

	dfs(1, 1);

	for (int i(1); i <= n; ++i)
	{
		insert(sum[i]);
	}

	printf("%lld\n", solve(0, logW));
	return 0;
}
