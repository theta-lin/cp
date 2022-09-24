void add_c(int x, int y)
{
	vc[++tc] = y, nc[tc] = hc[x], hc[x] = tc;
}

for (int x = 1; x <= n; ++x)
{
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (c[x] == c[y]) continue;
		add_c(c[x], c[y]);
	}
}
