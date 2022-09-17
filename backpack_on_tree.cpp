// 1826

#include <cstdio>
#include <vector>
#include <limits>

int n, m;

const int        maxN(100 + 10);
std::vector<int> edge[maxN];
int              dist[maxN];
int              w   [maxN];
int              f   [maxN][maxN][maxN];
int              g   [maxN];
int              size[maxN];

const int inf(std::numeric_limits<int>::max() / 2);

void dfs(int v)
{
	size[v] = 1;
	for (int i(0); i <= n; ++i)
	{
		f[v][i][0] = (dist[v] - dist[i]) * w[v];
	}

	for (size_t i(0); i < edge[v].size(); ++i)
	{
		int to(edge[v][i]);
		dist[to] += dist[v];
		dfs(to);
		for (int j(0); j <= n; ++j)
		{
			for (int k(0); k <= size[v] + size[to] && k <= m; ++k)
			{
				g[k] = inf;
			}
			for (int k(0); k <= size[v] && k <= m; ++k)
			{
				for (int l(0); l <= size[to] && k + l <= m; ++l)
				{
					g[k + l] = std::min(g[k + l], f[v][j][k] + f[to][j][l]);
				}
			}
			for (int k(0); k <= size[v] && k <= m; ++k)
			{
				for (int l(0); l <= size[to] && k + l + 1 <= m; ++l)
				{
					g[k + l + 1] = std::min(g[k + l + 1], f[v][j][k] + f[to][to][l]);
				}
			}
			for (int k(0); k <= size[v] + size[to] && k <= m; ++k)
			{
				f[v][j][k] = g[k];
			}
		}
		size[v] += size[to];
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i(1); i <= n; ++i)
	{
		int v;
		scanf("%d %d %d", &w[i], &v, &dist[i]);
		edge[v].push_back(i);
	}

	dfs(0);

	printf("%d\n", f[0][0][m]);
	return 0;
}
