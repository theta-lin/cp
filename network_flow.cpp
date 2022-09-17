#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

const int maxN(5000);

int to   [maxN];
int pre  [maxN];
int last [maxN];
int cap  [maxN];
int depth[maxN];

const int inf(0x3f3f3f3f);

bool bfs(int start, int end)
{
	memset(depth, 0, sizeof(depth));
	depth[start] = 1;

	std::queue<int> queue;
	queue.push(start);
	while (!queue.empty())
	{
		int v(queue.front());
		queue.pop();
		for (int e(last[v]); e; e = pre[e])
		{
			if (!depth[to[e]] && cap[e])
			{
				depth[to[e]] = depth[v] + 1;
				queue.push(to[e]);
			}
		}
	}

	return depth[end];
}

int dfs(int v, int end, int flow)
{
	if (!flow) return 0;
	if (v == end) return flow;

	int sum(0);
	for (int e(last[v]); flow && e; e = pre[e])
	{
		if (depth[v] + 1 == depth[to[e]])
		{
			int cur(dfs(to[e], end, std::min(flow, cap[e])));
			cap[e] -= cur;
			cap[e ^ 1] += cur;
			flow -= cur;
			sum += cur;
		}
	}

	if (!sum) depth[v] = 0;
	return sum;
}

void addEdge(int u, int v, int w)
{
	static int lastEdge(2);

	to[lastEdge] = v;
	pre[lastEdge] = last[u];
	last[u] = lastEdge;
	cap[lastEdge] = w;
	++lastEdge;

	to[lastEdge] = u;
	pre[lastEdge] = last[v];
	last[v] = lastEdge;
	++lastEdge;
}

int main()
{
	int m, n;
	std::cin >> m >> n;

	for (int i(1); i <= m; ++i)
		addEdge(0, i, 1);

	while (true)
	{
		int a, b;
		std::cin >> a >> b;
		if (a == -1)
			break;
		addEdge(a, b, 1);
	}

	for (int i(m + 1); i <= n; ++i)
		addEdge(i, n + 1, 1);

	int sum(0);
	while (bfs(0, n + 1))
	{
		sum += dfs(0, n + 1, inf);
	}

	if (sum)
		std::cout << sum << std::endl;
	else
		std::cout << "No Solution!" << std::endl;

	return 0;
}
