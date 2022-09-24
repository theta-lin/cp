// 5202

#include <cstdio>
#include <cctype>

const int       maxN(2000000 + 10);
const long long mod (1000000007);
long long       ans;
int             to  [maxN];
int             pre [maxN];
int             last[maxN];
long long       inv [maxN];
long long       sum [maxN];

int read()
{
	char ch(0);
	while (!isdigit(ch))
	{
		ch = getchar();
	}
	int result(0);
	while (isdigit(ch))
	{
		result = result * 10 + int(ch - '0');
		ch = getchar();
	}
	return result;
}

void addEdge(int u, int v)
{
	static int lastEdge(0);
	++lastEdge;
	to[lastEdge] = v;
	pre[lastEdge] = last[u];
	last[u] = lastEdge;
}

void dfs(int v, int pred, int depth)
{
	ans = (ans + sum[depth]) % mod;
	for (int e(last[v]); e; e = pre[e])
	{
		if (to[e] != pred)
		{
			dfs(to[e], v, depth + 1);
		}
	}
}

int main()
{
	int n(read());
	for (int v(2); v <= n; ++v)
	{
		int a(read());
		addEdge(a, v);
	}

	inv[1] = 1;
	sum[1] = 1;
	for (int i(2); i <= n; ++i)
	{
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		sum[i] = (sum[i - 1] + inv[i]) % mod;
	}

	dfs(1, 0, 0);

	printf("%lld\n", ans);
	return 0;
}
