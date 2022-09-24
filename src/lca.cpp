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
