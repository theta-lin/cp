const int N = 105;
int w[N][N];
int la[N], lb[N];
bool va[N], vb[N];
int match[N];
int n, delta;

bool dfs(int x)
{
	va[x] = 1;
	for (int y = 1; y <= n; ++y)
	{
		if (!vb[y])
		{
			if (la[x] + lb[y] - w[x][y] == 0)
			{
				vb[y] = 1;
				if (!match[y] || dfs(match[y]))
				{
					match[y] = x;
					return true;
				}
			}
		}
		else delta = min(delta, la[x] + lb[y] - w[x][y]);
	}
	return false;
}

int KM()
{
	for (int i = 1; i <= n; ++i)
	{
		la[i] = -(1 << 30);
		lb[i] = 0;
		for (int j = 1; j <= n; ++j)
			la[i] = max(la[i], w[i][j]);
	}
	for (int i = 1; i <= n; ++i)
	{
		while (true)
		{
			memset(va, 0, sizeof(va));
			memset(vb, 0, sizeof(vb));
			delta = 1 << 30;
			if (dfs(i)) break;
			for (int j = 1; j <= n; ++j)
			{
				if (va[j]) la[j] -= delta;
				if (vb[j]) lb[j] += delta;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) ans += w[match[i]][i];
	return ans;
}
