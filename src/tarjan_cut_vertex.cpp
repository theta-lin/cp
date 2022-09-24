const int SIZE = 100010;
int head[SIZE], ver[SIZE * 2], Next[SIZE * 2];
int dfn[SIZE], low[SIZE], stack[SIZE];
int n, m, tot, num, root;
bool cut[SIZE];

void add(int x, int y)
{
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void tarjan(int x)
{
	dfn[x] = low[x] = ++num;
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
			}
		}
		else low[x] = min(low[x], dfn[y]);
	}
}

int main()
{
	cin >> n >> m;
	tot = 1;
	for (int i = 1; i <= m; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if (x == y) continue;
		add(x, y), add(y, x);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) root = i, tarjan(i);
	for (int i = 1; i <= n; ++i)
		if (cut[i]) printf("%d ", i);
	puts("are cut-vertexes");
}
