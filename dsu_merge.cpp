// 5287

#include <cstdio>
#include <unordered_map>
#include <queue>

const int maxN(300000 + 10);
int f   [maxN];
int size[maxN];
std::unordered_map<int, int> in[maxN];

int unionFind(int v)
{
	if (f[v] == v)
	{
		return v;
	}
	else
	{
		return f[v] = unionFind(f[v]);
	}
}

std::queue<std::pair<int, int> > queue;

void merge(int u, int v)
{
	u = unionFind(u);
	v = unionFind(v);
	if (u == v) return;
	if (size[u] > size[v]) std::swap(u, v);
	size[v] += size[u];
	f[u] = v;

	for (std::unordered_map<int, int>::iterator it(in[u].begin()); it != in[u].end(); ++it)
	{
		if (in[v][it->first])
		{
			queue.push(std::make_pair(it->second, in[v][it->first]));
		}
		else
		{
			in[v][it->first] = it->second;
		}
	}
}

int main()
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for (int v(1); v <= n; ++v)
	{
		f[v] = v;
		size[v] = 1;
	}
	for (int e(1); e <= m; ++e)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		if (in[v][w])
		{
			queue.push(std::make_pair(u, in[v][w]));
		}
		else
		{
			in[v][w] = u;
		}
	}

	while (!queue.empty())
	{
		std::pair<int, int> pair(queue.front());
		queue.pop();
		merge(pair.first, pair.second);
	}

	long long ans(0);
	for (int v(1); v <= n; ++v)
	{
		if (f[v] == v)
		{
			ans += 1ll * size[v] * (size[v] - 1) / 2;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
