void tarjan(int x)
{
	dfn[x] = low[x] = ++num;
	stack[++top] = x;
	if (x == root && head[x] == 0)
	{
		dcc[++cnt].push_back(x);
		return;
	}

	int flag = 0;
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (!dfn[y])
		{
			tarjan(y);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x])
			{
				++flag;
				if (x != root || flag > 1) cut[x] = true;
				++cnt;
				int z;
				do
				{
					z = stack[top--];
					dcc[cnt].push_back(z);
				}
				while (z != y);
				dcc[cnt].push_back(x);
			}
		}
		else low[x] = min(low[x], dfn[y]);
	}
}

for (int i = 1; i <= cnt; ++i)
{
	printf("e-DCC #%d:", i);
	for (int j = 0; j < dcc[i].size(); ++j)
		printf(" %d", dcc[i][j]);
	puts("");
}
