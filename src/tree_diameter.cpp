// Or: DFS twice

void dp(int x)
{
	v[x] = 1;
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (v[y]) continue;
		dp(y);
		ans = max(ans, d[x] + d[y] + edge[i]);
		d[x]= max(d[x], d[y] + edge[i]);
	}
}
