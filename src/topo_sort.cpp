// 4602

#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <utility>
#include <bitset>
#include <vector>
#include <cstdio>

int       n, m;
long long ans(0);
int       to  [1200000 + 10];
int       pre [1200000 + 10];
long long cost[1200000 + 10];
int       last[30000   + 10];
long long dist[30000   + 10];
bool      go  [30000   + 10];
long long deg [30000   + 10];

struct Cmp
{
	bool operator()(int a, int b)
	{
		return dist[a] > dist[b];
	}
};

std::bitset<30000 + 10> state[30000 + 10];
std::queue<int> queue;
std::priority_queue<int, std::vector<int>, Cmp> pqueue;

void dijkstra()
{
	memset(dist, 0x30, sizeof(dist));
	dist[1] = 0;
	pqueue.push(1);

	while (!pqueue.empty())
	{
		if (!go[pqueue.top()])
		{
			go[pqueue.top()] = true;
			for (int i(last[pqueue.top()]); i != -1; i = pre[i])
			{
				if (!go[to[i]] && dist[to[i]] > dist[pqueue.top()] + cost[i])
				{
					dist[to[i]] = dist[pqueue.top()] + cost[i];
					pqueue.push(to[i]);
				}
			}
		}
		pqueue.pop();
	}
}

void init()
{
	memset(deg, -1, sizeof(deg));
	deg[n] = 0;
	queue.push(n);
	while (!queue.empty())
	{
		for (int i(last[queue.front()]); i != -1; i = pre[i])
		{
			if (dist[queue.front()] == dist[to[i]] + cost[i])
			{
				if (deg[to[i]] == -1)
				{
					deg[to[i]] = 1;
					queue.push(to[i]);
				}
				else
				{
					++deg[to[i]];
				}
			}
		}
		queue.pop();
	}
}

void topoSort()
{
	queue.push(n);
	while (!queue.empty())
	{
		ans += state[queue.front()].count();
  		state[queue.front()].set(queue.front());

		for (int i(last[queue.front()]); i != -1; i = pre[i])
		{
			if (deg[to[i]] > 0)
			{
				--deg[to[i]];
				state[to[i]] |= state[queue.front()];
				if (deg[to[i]] == 0)
					queue.push(to[i]);
			}
		}
		queue.pop();
	}
}

int main()
{
	memset(last, -1, sizeof(last));

	scanf("%d%d", &n, &m);
	for (int i(0); i < m; ++i)
	{
		int a, b;
		long long c;
		scanf("%d%d%lld", &a, &b, &c);
		to[i * 2] = b;
		pre[i * 2] = last[a];
		last[a] = i * 2;
		cost[i * 2] = c;

		to[i * 2 + 1] = a;
		pre[i * 2 + 1] = last[b];
		last[b] = i * 2 + 1;
		cost[i * 2 + 1] = c;
	}

	dijkstra();
	init();
	topoSort();

	printf("%lld\n", ans);
	return 0;
}
