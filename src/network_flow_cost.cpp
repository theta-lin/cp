// 5379

#include <cstdio>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <queue>

struct Pig
{
	long long x;
	long long y;
	long long c;

	Pig() : x(0), y(0), c(0)
	{
	}

	Pig(long long x, long long y, long long c = 0) : x(x), y(y), c(c)
	{
	}
};

long long diff(const Pig &a, const Pig &b)
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

const int maxN (1000 + 10);
const int maxV (3 * maxN);
const int maxE (40 * maxN);
Pig       a    [maxN];
Pig       b    [maxN];
int       to   [maxE];
int       pre  [maxE];
long long cost [maxE];
long long cap  [maxE];
int       last [maxV];
long long flow [maxV];
long long dist [maxV];
bool      visit[maxV];
int       in   [maxV];

const long long inf(std::numeric_limits<long long>::max() / 10);

void addEdge(int u, int v, long long w, long long c)
{
	static int lastEdge(1);

	++lastEdge;
	to[lastEdge] = v;
	pre[lastEdge] = last[u];
	last[u] = lastEdge;
	cost[lastEdge] = w;
	cap[lastEdge] = c;

	++lastEdge;
	to[lastEdge] = u;
	pre[lastEdge] = last[v];
	last[v] = lastEdge;
	cost[lastEdge] = -w;
	cap[lastEdge] = 0;
}

bool SPFA(int S, int T)
{
	for (int i(0); i < maxV; ++i)
	{
		flow[i] = 0;
		dist[i] = -inf;
		visit[i] = false;
	}

	flow[S] = inf;
	dist[S] = 0;
	in[T] = -1;
	std::queue<int> queue;
	queue.push(S);
	visit[S] = true;

	while (!queue.empty())
	{
		int v(queue.front());
		queue.pop();
		visit[v] = false;
		for (int e(last[v]); e; e = pre[e])
		{
			if (cap[e] && dist[to[e]] < dist[v] + cost[e])
			{
				dist[to[e]] = dist[v] + cost[e];
				flow[to[e]] = std::min(flow[v], cap[e]);
				in[to[e]] = e;
				if (!visit[to[e]])
				{
					queue.push(to[e]);
					visit[to[e]] = true;
				}
			}
		}
	}

	return in[T] != -1;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i(1); i <= n; ++i)
	{
		scanf("%lld %lld %lld", &a[i].x, &a[i].y, &a[i].c);
	}
	for (int i(1); i <= n; ++i)
	{
		scanf("%lld %lld %lld", &b[i].x, &b[i].y, &b[i].c);
	}

	int S(2 * n + 1), T(2 * n + 2);
	int DL(2 * n + 3), UR(2 * n + 4), DR(2 * n + 5), UL(2 * n + 6);
	Pig cornerDL(0, 0), cornerDR(0, 1000000001);

	for (int i(1); i <= n; ++i)
	{
		addEdge(S, i, 0, a[i].c);
		addEdge(n + i, T, 0, b[i].c);

		addEdge(i, DL, diff(a[i], cornerDL), inf);
		addEdge(DL, n + i, -diff(cornerDL, b[i]), inf);

		addEdge(i, UR, -diff(a[i], cornerDL), inf);
		addEdge(UR, n + i, diff(cornerDL, b[i]), inf);

		addEdge(i, DR, diff(a[i], cornerDR), inf);
		addEdge(DR, n + i, -diff(cornerDR, b[i]), inf);

		addEdge(i, UL, -diff(a[i], cornerDR), inf);
		addEdge(UL, n + i, diff(cornerDR, b[i]), inf);
	}

	long long ans(0);
	while (SPFA(S, T))
	{
		ans += flow[T] * dist[T];
		for (int cur(T); cur != S; cur = to[in[cur] ^ 1])
		{
			cap[in[cur]] -= flow[T];
			cap[in[cur] ^ 1] += flow[T];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
