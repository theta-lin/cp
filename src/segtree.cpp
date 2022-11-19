// 3487

#include <cmath>

const     int maxN (300000);
constexpr int upN  (1 << int(std::ceil(std::log2(maxN)) + 1));
const     int inf  (0x3f3f3f3f);
int           min  [upN + 10];
int           cnt  [upN + 10];
int           delta[upN + 10];

void init(int node, int tl, int tr)
{
	min[node] = inf;
	cnt[node] = tr - tl + 1;
	if (tl != tr)
	{
		int mid((tl + tr) / 2);
		init(node * 2, tl, mid);
		init(node * 2 + 1, mid + 1, tr);
	}
}

void pushDown(int node, bool leaf)
{
	if (!leaf)
	{
		min[node * 2] += delta[node];
		delta[node * 2] += delta[node];
		min[node * 2 + 1] += delta[node];
		delta[node * 2 + 1] += delta[node];
	}
	delta[node] = 0;
}

void pushUp(int node)
{
	if (min[node * 2] == min[node * 2 + 1])
	{
		min[node] = min[node * 2];
		cnt[node] = cnt[node * 2] + cnt[node * 2 + 1];
	}
	else if (min[node * 2] < min[node * 2 + 1])
	{
		min[node] = min[node * 2];
		cnt[node] = cnt[node * 2];
	}
	else
	{
		min[node] = min[node * 2 + 1];
		cnt[node] = cnt[node * 2 + 1];
	}
}

void add(int node, int tl, int tr, int l, int r, int value)
{
	//if (node == 1) printf("ADD %d,%d %d\n", l, r, value);
	pushDown(node, tl == tr);
	if (l <= tl && tr <= r)
	{
		min[node] += value;
		delta[node] += value;
	}
	else
	{
		int mid((tl + tr) / 2);
		if (l <= mid) add(node * 2, tl, mid, l, r, value);
		if (r >= mid + 1) add(node * 2 + 1, mid + 1, tr, l, r, value);
		pushUp(node);
	}
}

void modify(int node, int tl, int tr, int l, int r, int value)
{
	//if (node == 1) printf("MODIFY %d,%d %d\n", l, r, value);
	pushDown(node, tl == tr);
	if (l <= tl && tr <= r)
	{
		min[node] = value;
	}
	else
	{
		int mid((tl + tr) / 2);
		if (l <= mid) modify(node * 2, tl, mid, l, r, value);
		if (r >= mid + 1) modify(node * 2 + 1, mid + 1, tr, l, r, value);
		pushUp(node);
	}
}
