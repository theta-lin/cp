void dfs(int x, int color)
{
	v[x] = color
	for (int i = head[x]; i; i = Next[i])
	{
		if (v[y] == 0)
		{
			dfs(y, 3 - color)
		}
		else if (v[y] != color)
		{
			isBigraph = false;
		}
	}
}

for (int i = 1; i <= N; ++i)
{
	if (v[i] == 0)
	{
		dfs(i, 1);
	}
}
