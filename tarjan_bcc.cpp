// 1536

#include <iostream>
#include <cstring>
#include <stack>
#include <algorithm>

struct Edges
{
	int to  [200000 * 2 + 10];
	int pre [200000 * 2 + 10];
	int last[100000     + 10];

	Edges()
	{
		memset(last, -1, sizeof(last));
	}

	void addEdge(int a, int b)
	{
		static int size(0);
		to[size] = b;
		pre[size] = last[a];
		last[a] = size;
		++size;
	}
};

Edges map;
Edges tree;
std::stack<int> stack;

int dfn  [100000 + 10];
int low  [100000 + 10];
int bcc  [100000 + 10];
int lca  [100000 + 10][20];
int pred [100000 + 10];
int depth[100000 + 10];

int currentDfn(1);
int currentBcc(1);

void tarjan(int vertex, int inEdge)
{
	low[vertex] = dfn[vertex] = currentDfn++;
	stack.push(vertex);
	for (int i(map.last[vertex]); i != -1; i = map.pre[i])
	{
		if (i == (inEdge ^ 1))
			continue;

		if (dfn[map.to[i]])
		{
			low[vertex] = std::min(low[vertex], dfn[map.to[i]]);
		}
		else
		{
			tarjan(map.to[i], i);
			low[vertex] = std::min(low[vertex], low[map.to[i]]);
		}
	}

	if (dfn[vertex] == low[vertex])
	{
		bool below(true);
		while (below)
		{
			bcc[stack.top()] = currentBcc;
			if (stack.top() == vertex)
				below = false;
			stack.pop();
		}
		++currentBcc;
	}
}

void dfs(int vertex, int inVertex, int d)
{
	lca[vertex][0] = inVertex;
	for (int i(1); i < 20; ++i)
        lca[vertex][i] = lca[lca[vertex][i - 1]][i - 1];
	depth[vertex] = d;
	for (int i(tree.last[vertex]); i != -1; i = tree.pre[i])
	{
		if (tree.to[i] != inVertex)
			dfs(tree.to[i], vertex, d + 1);
	}
}

int getLca(int v1, int v2)
{
	if (depth[v1] < depth[v2])
		std::swap(v1, v2);
	for (int i(19); i >= 0; --i)
	{
		if (depth[v1] - (1 << i) >= depth[v2])
			v1 = lca[v1][i];
	}
	if (v1 == v2)
		return v1;
	for (int i(19); i >= 0; --i)
	{
		if (lca[v1][i] != lca[v2][i])
		{
			v1 = lca[v1][i];
			v2 = lca[v2][i];
		}
	}
	return lca[v1][0];
}

int get(int vertex)
{
	if (vertex == pred[vertex])
		return vertex;
	else
		return pred[vertex] = get(pred[vertex]);
}

int link(int vertex, int ancestor)
{
	int i(get(vertex));
	int count(0);
	while (depth[i] > depth[ancestor])
	{
		pred[i] = lca[i][0];
		++count;
		i = get(i);
	}
	//std::cout << '!' << vertex << ' ' << ancestor << ' ' << count << std::endl;
	return count;
}

int main()
{
	int N, M;
	std::cin >> N >> M;
	for (int i(1); i <= M; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		map.addEdge(a, b);
		map.addEdge(b, a);
	}

	tarjan(1, -1);

	int bridge(0);
	for (int from(1); from <= N; ++from)
	{
		//std::cout << from << ':' << bcc[from] << std::endl;
		for (int i(map.last[from]); i != -1; i = map.pre[i])
		{
			//std::cout << from << "->" << map.to[i]
			//   << ':' << bcc[from] << "->" << bcc[map.to[i]] << std::endl;
			if (bcc[from] != bcc[map.to[i]])
			{
				tree.addEdge(bcc[from], bcc[map.to[i]]);
				++bridge;
			}
		}
	}
	bridge /= 2;

	dfs(1, 0, 1);
	for (int i(1); i < currentBcc; ++i)
		pred[i] = i;

	int Q;
	std::cin >> Q;
	for (int i(1); i <= Q; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		if (bcc[a] == bcc[b])
		{
			std::cout << bridge << '\n';
		}
		else
		{
			int ancestor(getLca(bcc[a], bcc[b]));
			bridge -= link(bcc[a], ancestor);
			bridge -= link(bcc[b], ancestor);
			std::cout << bridge << '\n';
		}
	}

	return 0;
}
