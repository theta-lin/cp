// Connected, exactly two odd vertices

int head[100010], ver[1000010], Next[1000010], tot;
int stack[1000010], ans[1000010];
bool vis[1000010];
int n, m, top, t;

void add(int x, int y)
{
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void euler()
{
	stack[++top] = 1;
	while (top > 0)
	{
		int x = stack[top], i = head[x];
		while (i && vis[i]) i = Next[i];
		if (i)
		{
			stack[++top] = ver[i];
			vis[i] = vis[i ^ 1] = true;
			head[x] = Next[i];
		}
		else
		{
			--top;
			ans[++t] = x;
		}
	}
}

int main()
{
	cin >> n >> m;
	tot = 1;
	for (int i = 1; i <= m; ++i)
	{
		int x, y; scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	euler();
	for (int i = t; i; --i) printf("%d\n", ans[i]);
}
