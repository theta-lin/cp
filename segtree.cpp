// 3487

#include <cstdio>
#include <stack>

struct Range
{
	int l;
	int value;
};

const int maxN (300000 + 10);
const int inf  (0x3f3f3f3f);
int       P    [maxN];
int       min  [maxN * 8];
int       cnt  [maxN * 8];
int       delta[maxN * 8];

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

void pushDown(int node)
{
	min[node * 2] += delta[node];
	delta[node * 2] += delta[node];
	min[node * 2 + 1] += delta[node];
	delta[node * 2 + 1] += delta[node];
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
	pushDown(node);
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
	pushDown(node);
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

int main()
{
	int N;
	scanf("%d", &N);
	for (int i(1); i <= N; ++i)
	{
		scanf("%d", &P[i]);
	}

	// max - min - r + l = 0
	long long ans(0);
	init(1, 1, N);
	std::stack<Range> minStack, maxStack;
	for (int r(1); r <= N; ++r)
	{
		modify(1, 1, N, r, r, 1);
		add(1, 1, N, 1, r, -1);

		Range curMin = {r, P[r]};
		while (!minStack.empty() && curMin.value <= minStack.top().value)
		{
			add(1, 1, N, minStack.top().l, curMin.l - 1, -(curMin.value - minStack.top().value));
			curMin.l = minStack.top().l;
			minStack.pop();
		}
		minStack.push(curMin);

		Range curMax = {r, P[r]};
		while (!maxStack.empty() && curMax.value >= maxStack.top().value)
		{
			add(1, 1, N, maxStack.top().l, curMax.l - 1, curMax.value - maxStack.top().value);
			curMax.l = maxStack.top().l;
			maxStack.pop();
		}
		maxStack.push(curMax);

		if (min[1] == 0)
		{
			ans += cnt[1];
		}
	}

	printf("%lld\n", ans);
	return 0;
}
