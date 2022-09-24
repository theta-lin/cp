// 5380

#include <cstdio>
#include <algorithm>
#include <vector>

struct Node
{
	long long sum;
	long long diam;
	int end[2];
};

int n, m;

const int        maxN  (400000 + 10);
const int        maxLbN(30);
std::vector<int> edge  [maxN];
std::vector<int> cost  [maxN];
std::vector<int> goal  [maxN];
long long        in    [maxN];
long long        prefix[maxN];
int              depth [maxN];
int              euler [maxLbN][maxN * 2];
int              enter [maxN];
int              lb    [maxN * 2];
Node             data  [maxN * maxLbN];
int              lCh   [maxN * maxLbN];
int              rCh   [maxN * maxLbN];
int              root  [maxN];

inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
    return x;
}

int curEuler(0);

void dfs(int v, int pred)
{
	depth[v] = depth[pred] + 1;
	euler[0][++curEuler] = v;
	enter[v] = curEuler;
	for (size_t i(0); i < edge[v].size(); ++i)
	{
		int to(edge[v][i]);
		prefix[to] = prefix[v] + cost[v][i];
		dfs(to, v);
		euler[0][++curEuler] = v;
	}
}

int lca(int a, int b)
{
	a = enter[a];
	b = enter[b];
	if (a > b) std::swap(a, b);
	int lbLen(lb[b - a + 1]);
	int x(euler[lbLen][a]), y(euler[lbLen][b - (1 << lbLen) + 1]);
	return depth[x] < depth[y] ? x : y;
}

long long dist(int a, int b)
{
	if (a == 0 || b == 0) return 0;
	int l(lca(a, b));
	return prefix[a] + prefix[b] - 2 * prefix[l];
}

Node operator+(const Node &a, const Node &b)
{
	if (!b.end[0]) return a;
	if (!a.end[0]) return b;

	Node cur;
	cur.sum = a.sum + b.sum;
	cur.diam = 0;
	cur.end[0] = cur.end[1] = 0;

	int end[4] = {a.end[0], a.end[1], b.end[0], b.end[1]};
	for (int i(0); i < 4; ++i)
	{
		for (int j(i + 1); j < 4; ++j)
		{
			if (end[i] != 0 && end[j] != 0)
			{
				long long d(dist(end[i], end[j]));
				if (d >= cur.diam)
				{
					cur.diam = d;
					cur.end[0] = end[i];
					cur.end[1] = end[j];
				}
			}
		}
	}

	return cur;
}

int curNode(0);

void insert(int &node, int tl, int tr, int d, int v)
{
	if (!node) node = ++curNode;

	if (tl == tr)
	{
		data[node].sum = in[v] * 2;
		data[node].end[0] = data[node].end[1] = v;
	}
	else
	{
		int mid((tl + tr) / 2);
		if (d <= mid)
		{
			insert(lCh[node], tl, mid, d, v);
		}
		else
		{
			insert(rCh[node], mid + 1, tr, d, v);
		}
		data[node] = data[lCh[node]] + data[rCh[node]];
	}
}

int merge(int lNode, int rNode, int tl, int tr)
{
	if (!rNode) return lNode;
	if (!lNode) return rNode;

	if (tl == tr)
	{
		data[lNode] = data[lNode] + data[rNode];
		return lNode;
	}
	else
	{
		int mid((tl + tr) / 2);
		lCh[lNode] = merge(lCh[lNode], lCh[rNode], tl, mid);
		rCh[lNode] = merge(rCh[lNode], rCh[rNode], mid + 1, tr);
		data[lNode] = data[lCh[lNode]] + data[rCh[lNode]];
		return lNode;
	}
}

Node query(int node, int tl, int tr, int l, int r)
{
	if (!node || (l <= tl && tr <= r))
	{
		return data[node];
	}
	else
	{
		int mid((tl + tr) / 2);
		if (r <= mid)
		{
			return query(lCh[node], tl, mid, l, r);
		}
		else if (l >= mid + 1)
		{
			return query(rCh[node], mid + 1, tr, l, r);
		}
		else
		{
			return query(lCh[node], tl, mid, l, r) + query(rCh[node], mid + 1, tr, l, r);
		}
	}
}

long long ans(0);

void solve(int v)
{
	insert(root[v], 1, n, depth[v], v);
	for (size_t i(0); i < edge[v].size(); ++i)
	{
		int to(edge[v][i]);
		solve(to);
		root[v] = merge(root[v], root[to], 1, n);
	}

	for (size_t i(0); i < goal[v].size(); ++i)
	{
		Node result(query(root[v], 1, n, depth[v], std::min(depth[v] + goal[v][i], n)));
		ans ^= result.sum - result.diam - in[v] * 2;
	}
}

int main()
{
	n = read();
	m = read();
	for (int i(2); i <= n; ++i)
	{
		int p(read()), w(read());
		edge[p].push_back(i);
		cost[p].push_back(w);
		in[i] = w;
	}
	for (int i(1); i <= m; ++i)
	{
		int r, d;
		scanf("%d %d", &r, &d);
		goal[r].push_back(d);
	}

	dfs(1, 0);
	lb[0] = -1;
	for (int i(1); i <= curEuler; ++i)
	{
		lb[i] = lb[i / 2] + 1;
	}
	for (int i(1); i < maxLbN; ++i)
	{
		for (int j(1); j + (1 << i) - 1 <= curEuler; ++j)
		{
			int a(euler[i - 1][j]), b(euler[i - 1][j + (1 << (i - 1))]);
			euler[i][j] = (depth[a] <= depth[b] ? a : b);
		}
	}

	solve(1);
	printf("%lld\n", ans);
	return 0;
}
