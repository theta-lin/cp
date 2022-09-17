// 2409

#include <cstdio>
#include <iostream>
#include <cstring>

int n;
const int maxN(131072);
//const int maxN(5000);
char op[16];
bool test(false);

class Segtree
{
private:
	const int opInstall = 1;
	const int opUninstall = 2;

	int count[maxN * 4 + 10];
	int lazy [maxN * 4 + 10];

	void pushDown(int node, int left, int right);
	void pushUp(int node);

public:
	int install(int node, int left, int right, int oLeft, int oRight);
	int uninstall(int node, int left, int right, int oLeft, int oRight);
	int query(int node, int left, int right, int pos);
};

void Segtree::pushDown(int node, int left, int right)
{
	//if (left == right)
	//if (node >= 2 * n)
	//	std::cout << node << ' ' << left << ' ' << right <<  '\n';
	//std::cout << "!!!" << opInstall << ' ' << opUninstall << '\n';
	if (lazy[node] == opInstall)
	{
		lazy[node] = 0;
		lazy[node * 2] = opInstall;
		lazy[node * 2 + 1] = opInstall;

		int mid((left + right) / 2);
		int lSize(mid - left + 1);
		int rSize(right - mid);
		count[node * 2] = lSize;
		count[node * 2 + 1] = rSize;
	}

	if (lazy[node] == opUninstall)
	{
		lazy[node] = 0;
		lazy[node * 2] = opUninstall;
		lazy[node * 2 + 1] = opUninstall;

		count[node * 2] = 0;
		count[node * 2 + 1] = 0;
	}
}

void Segtree::pushUp(int node)
{
	count[node] = count[node * 2] + count[node * 2 + 1];
}

int Segtree::install(int node, int left, int right, int oLeft, int oRight)
{
	//std::cout << "###" << left << '-' << right << ' ' << lazy[node] << ' ' << count[24] << '\n';
	pushDown(node, left, right);
	int sum(0);
	if (left >= oLeft && right <= oRight)
	{
		int size(right - left + 1);
		sum += size - count[node];
		lazy[node] = opInstall;
		count[node] = size;
	}
	else
	{
		int mid((left + right) / 2);
		if (oLeft <= mid) sum += install(node * 2, left, mid, oLeft, oRight);
		if (oRight >= mid + 1) sum += install(node * 2 + 1, mid + 1, right, oLeft, oRight);
		pushUp(node);
	}
	//std::cout << "INSTALL: " << left << '-' << right << ' ' << oLeft << '-' << oRight << ' ' << count[node] << ' ' << sum << '\n';
	return sum;
}

int Segtree::uninstall(int node, int left, int right, int oLeft, int oRight)
{
	pushDown(node, left, right);
	//std::cout << "UNINSTALL: " << left << '-' << right << ' ' << oLeft << '-' << oRight << ' ' << count[node] << '\n';
	int sum(0);
	if (left >= oLeft && right <= oRight)
	{
		sum += count[node];
		lazy[node] = opUninstall;
		count[node] = 0;
	}
	else
	{
		int mid((left + right) / 2);
		if (oLeft <= mid) sum += uninstall(node * 2, left, mid, oLeft, oRight);
		if (oRight >= mid + 1) sum += uninstall(node * 2 + 1, mid + 1, right, oLeft, oRight);
		pushUp(node);
	}
	return sum;
}

int Segtree::query(int node, int left, int right, int pos)
{
	pushDown(node, left, right);
	if (left == right)
	{
		return count[node];
	}
	else
	{
		int mid((left + right) / 2);
		if (pos <= mid) return query(node * 2, left, mid, pos);
		else return query(node * 2 + 1, mid + 1, right, pos);
	}
}

Segtree seg;

int to    [maxN * 2 + 10];
int pre   [maxN * 2 + 10];
int last  [maxN     + 10];

void addEdge(int x, int y)
{
	static int e(1);
	to[e] = y;
	pre[e] = last[x];
	last[x] = e;
	++e;
}

int father[maxN     + 10];
int depth [maxN     + 10];
int size  [maxN     + 10];
int heavy [maxN     + 10];
int top   [maxN     + 10];
int dfn   [maxN     + 10];

void dfsInfo(int v, int f, int d)
{
	father[v] = f;
	depth[v] = d;
	size[v] = 1;
	for (int e(last[v]); e; e = pre[e])
	{
		if (to[e] != f)
		{
			dfsInfo(to[e], v, d + 1);
			if (heavy[v] == -1 || size[to[e]] > size[heavy[v]])
				heavy[v] = to[e];
			size[v] += size[to[e]];
		}
	}
}

int currentDfn(0);
void dfsChain(int v, int begin)
{
	top[v] = begin;
	dfn[v] = currentDfn++;
	if (heavy[v] == -1)
		return;

	dfsChain(heavy[v], begin);
	for (int e(last[v]); e; e = pre[e])
	{
		if (to[e] != father[v] && to[e] != heavy[v])
			dfsChain(to[e], to[e]);
	}
}

int install(int v)
{
	int sum(0);
	while (v != -1)
	{
		sum += seg.install(1, 0, n - 1, dfn[top[v]], dfn[v]);
		v = father[top[v]];
	}
	return sum;
}

int uninstall(int v)
{
	int sum(0);
	sum += seg.uninstall(1, 0, n - 1, dfn[v], dfn[v] + size[v] - 1);
	return sum;
}

int main()
{
	//freopen("manager.in", "r", stdin);
	//freopen("manager.out", "w", stdout);

	scanf("%d", &n);
	for (int v(1); v <= n - 1; ++v)
	{
		int f;
		scanf("%d", &f);
		addEdge(f, v);
	}

	memset(heavy, -1, sizeof(heavy));
	dfsInfo(0, -1, 0);
	dfsChain(0, 0);

	//for (int v(0); v <= n - 1; ++v)
	//	std::cout << v << "->" << dfn[v] << '\n';

	int q;
	scanf("%d", &q);
	for (int i(1); i <= q; ++i)
	{
		int v;
		scanf("%s %d", op, &v);
		if (op[0] == 'i')
		{
			if (seg.query(1, 0, n - 1, dfn[v]) == 1)
				printf("0\n");
			else
				printf("%d\n", install(v));
		}
		else
		{
			if (seg.query(1, 0, n - 1, dfn[v]) == 0)
				printf("0\n");
			else
				printf("%d\n", uninstall(v));
		}
	}

	return 0;
}
