const int N = 100010, M = 1000010;
int ver[M], Next[M], head[N], dfn[N], low[N];
int stack[N], ins[N], c[N];
vector<int> scc[N];
int n, m, tot, num, top, cnt;

void add(int x, int y)
{
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void tarjan(int x)
{
	dfn[x] = low[x] = ++num;
	stack[++top] = x, ins[x] = 1;
	for (int i = head[x]; i; i = Next[i])
	{
		if (!dfn[ver[i]])
		{
			tarjan(ver[i]);
			low[x] = min(low[x], low[ver[i]]);
		}
		else if (ins[ver[i]])
			low[x] = min(low[x], low[ver[i]]);
	}

	if (dfn[x] == low[x])
	{
		++cnt; int y;
		do
		{
			y = stack[top--], ins[y] = 0;
			c[y] = cnt, scc[cnt].push_back(y);
		}
		while(x != y);
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);
}
