void dfs(int x)
{
	v[x] = 1;
	size[x] = 1;
	int max_part = 0;
	for (int i = head[x]; i; i = next[i])
	{
		int y = ver[i];
		if (v[x]) continue;
		dfs(y);
		size[x] += size[y];
		max_part = max(max_part, size[y]);
	}
	max_part = max(max_part, n - size[x]);
	if (max_part < ans)
	{
		ans = max_part;
		pos = x;
	}
}
