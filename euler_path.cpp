// 5186

#include <cstdio>
#include <cstring>

int       n, m;
const int maxN  (400000 + 10);
int       to    [maxN];
int       pre   [maxN];
int       last  [maxN];
int       degree[maxN];
int       visit [maxN];

int lastEdge;
void addEdge(int u, int v)
{
	++lastEdge;
	to[lastEdge] = v;
	pre[lastEdge] = last[u];
	last[u] = lastEdge;
}

bool dfs(int v, int pred, int cut)
{
	//printf("!%d\n", v);
	if (v == cut) return true;
	if (visit[v]) return false;
	visit[v] = true;

	for (int e(last[v]); e; e = pre[e])
	{
		if (to[e] != pred)
		{
			if (!dfs(to[e], v, cut))
			{
				return false;
			}
		}
	}

	return true;
}

bool check(int cut)
{
	//printf("check: %d\n", cut);

	memset(visit, false, sizeof(visit));
	for (int v(1); v <= n; ++v)
	{
		if (!visit[v])
		{
			if (!dfs(v, 0, cut))
			{
				return false;
			}
		}
	}

	return true;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int ttt(1); ttt <= T; ++ttt)
	{
		scanf("%d %d", &n, &m);
		lastEdge = 0;
		memset(last, 0, sizeof(last));
		memset(degree, 0, sizeof(degree));
		for (int e(1); e <= m; ++e)
		{
			int u, v;
			scanf("%d %d", &u, &v);
			addEdge(u, v);
			addEdge(v, u);
			++degree[u];
			++degree[v];
		}

		int cnt(0), max(0);
		for (int v(1); v <= n; ++v)
		{
			if (degree[v] % 2 == 1)
			{
				++cnt;
			}
			if (degree[v] > degree[max])
			{
				max = v;
			}
		}

		bool exist(false);
		if (cnt <= 2)
		{
			for (int v(1); v <= n; ++v)
			{
				if ((cnt && degree[v] % 2 == 1) || (!cnt && v == max))
				{
					if (check(v))
					{
						exist = true;
						break;
					}
				}
			}
		}

		puts(exist ? "YES" : "NO");
	}

	return 0;
}
