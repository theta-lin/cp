// 1231
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

struct Node
{
	int low;
	int high;
	int count;
};

int  to   [200000  + 10];
int  pre  [200000  + 10];
int  last [100000  + 10];
int  V    [100000  + 10];
int  depth[100000 + 10];
int  lca  [100000  + 10][20];
int  root [100000  + 10];
Node tree [2000000 + 10];
int  nextId(1);

int increase(int oldNode, int low, int high, int value)
{
	int newNode(nextId);
	++nextId;
	tree[newNode] = tree[oldNode];
	++tree[newNode].count;
	if (low != high)
	{
		int mid((low + high) / 2);
		if (value <= mid)
			tree[newNode].low = increase(tree[oldNode].low, low, mid, value);
		else
			tree[newNode].high = increase(tree[oldNode].high, mid + 1, high, value);
	}
	return newNode;
}

void dfs(int father, int v, int d)
{
	depth[v] = d;
	lca[v][0] = father;
	for (int i(1); (1 << i) <= depth[v]; ++i)
		lca[v][i] = lca[lca[v][i - 1]][i - 1];
	root[v] = increase(root[father], 0, 100000, V[v]);

	for (int i(last[v]); i != 0; i = pre[i])
	{
		if (to[i] != father)
			dfs(v, to[i], d + 1);
	}
}

int getLca(int u, int v)
{
	if (depth[u] < depth[v])
		std::swap(u, v);
	for (int i(19); i >= 0; --i)
	{
		if (depth[u] - (1 << i) >= depth[v])
			u = lca[u][i];
	}
	if (u == v)
		return u;

	for (int i(19); i >= 0; --i)
	{
		if (lca[u][i] != lca[v][i])
		{
			u = lca[u][i];
			v = lca[v][i];
		}
	}
	return lca[u][0];
}

int query(int uNode, int vNode, int lcaNode, int faLcaNode, int low, int high, int k)
{
	if (low == high)
		return low;
	int mid((low + high) / 2);
	int lowCount(  tree[tree[uNode].low].count + tree[tree[vNode].low].count
	             - tree[tree[lcaNode].low].count - tree[tree[faLcaNode].low].count);
	if (k <= lowCount)
		return query(tree[uNode].low, tree[vNode].low, tree[lcaNode].low, tree[faLcaNode].low, low, mid, k);
	else
		return query(tree[uNode].high, tree[vNode].high, tree[lcaNode].high, tree[faLcaNode].high, mid + 1, high, k - lowCount);
}

int main()
{
	int N, M;
	std::cin >> N >> M;
	for (int i(1); i <= N; ++i)
		std::cin >> V[i];
	for (int i(1); i <= N - 1; ++i)
	{
		int x, y;
		std::cin >> x >> y;
		to[i * 2 - 1] = y;
		pre[i * 2 - 1] = last[x];
		last[x] = i * 2 - 1;

		to[i * 2] = x;
		pre[i * 2] = last[y];
		last[y] = i * 2;
	}
	dfs(0, 1, 0);

	int lastAns(0);
	for (int i(1); i <= M; ++i)
	{
		int u, v, k;
		std::cin >> u >> v >> k;
		u ^= lastAns;
		int ans(query(root[u], root[v], root[getLca(u, v)], root[lca[getLca(u, v)][0]], 0, 100000, k));
		std::cout << ans << std::endl;
		lastAns = ans;
	}

	return 0;
}
