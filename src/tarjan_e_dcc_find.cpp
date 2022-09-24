int c[SIZE], dcc;
void dfs(int x)
{
	c[x] = dcc;
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (c[y] || bridge[i]) continue;
		dfs(y);
	}
}

for (int i = 1; i <= n; ++i)
{
	if (!c[i])
	{
		++dcc;
		dfs(i);
	}
}
printf("There are %d e-DCCs. \n", dcc);
for (int i = 1; i <= n; ++i)
	printf("%d belongs to DCC %d.\n", i, c[i]);
