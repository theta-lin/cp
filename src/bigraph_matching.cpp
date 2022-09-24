bool dfs(int x)
{
	for (int i = head[x], y; i; i = next[i])
	{
		if (!visit[y = ver[i]])
		{
			visit[y] = 1;
			if (!match[y] || dfs(match[y]))
			{
				match[y] = x; return true;
			}
		}
	}
	return false;
}

for (int i = 1; i <= n; ++i)
{
	memset(visit, 0, sizeof(visit));
	if (dfs(i)) ++ans;
}
