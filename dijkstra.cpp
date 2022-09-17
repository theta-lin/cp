dist[src] = 0;
std::priority_queue<std::pair<int, int>,
					std::vector<std::pair<int, int> >,
					std::greater<std::pair<int, int> > > heap;
heap.push(std::make_pair(dist[src], src));

while (!heap.empty())
{
	int v(heap.top().second);
	heap.pop();
	if (visited[v])	continue;
	visited[v] = true;

	for (int nxt(last[v]); nxt; nxt = pre[nxt])
	{
		if (!visited[to[nxt]] && dist[to[nxt]] > dist[v] + cost[nxt])
		{
			dist[to[nxt]] = dist[v] + cost[nxt];
			heap.push(std::make_pair(dist[to[nxt]], to[nxt]));
		}
	}
}
