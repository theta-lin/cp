// 1231
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <iostream>

struct Node
{
	int low;
	int high;
	int count;
};

int  number[100000 + 10];
int  sorted[100000 + 10];
int  root  [100000 + 10];
Node tree  [2000000 + 10];
int  nextId(0);

int read()
{
	char ch;
	while (ch = getchar(), !isdigit(ch) && ch != '-')
		;
	int ret(0);
	int sign(ch == '-' ? -1 : 1);
	if (sign == -1)
		ch = getchar();
	while (isdigit(ch))
	{
		ret = ret * 10 + static_cast<int>(ch - '0');
		ch = getchar();
	}
	return sign * ret;
}

int increase(int oldNode, int low, int high, int value)
{
	int newNode(nextId);
	++nextId;
	tree[newNode] = tree[oldNode];
	++tree[newNode].count;
	if (low != high)
	{
		int mid((low + high) / 2);
		if (value <= mid)
			tree[newNode].low = increase(tree[oldNode].low, low, mid, value);
		else
			tree[newNode].high = increase(tree[oldNode].high, mid + 1, high, value);
	}
	return newNode;
}

int query(int leftNode, int rightNode, int low, int high, int k)
{
	if (low == high)
		return low;
	int mid((low + high) / 2);
	int lowCount(tree[tree[rightNode].low].count - tree[tree[leftNode].low].count);
	if (k <= lowCount)
		return query(tree[leftNode].low, tree[rightNode].low, low, mid, k);
	else
		return query(tree[leftNode].high, tree[rightNode].high, mid + 1, high, k - lowCount);
}

int main()
{
	int n(read()), m(read());
	for (int i(1); i <= n; ++i)
		sorted[i] = number[i] = read();

	std::sort(sorted + 1, sorted + n + 1);
	int *sortedEnd(std::unique(sorted + 1, sorted + n + 1));
	for (int i(1); i <= n; ++i)
		number[i] = std::lower_bound(sorted + 1, sortedEnd, number[i]) - sorted;
	int maxNumber(sortedEnd - sorted);

	++nextId;
	for (int i(1); i <= n; ++i)
		root[i] = increase(root[i - 1], 1, maxNumber, number[i]);

	for (int i(1); i <= m; ++i)
	{
		int l, r, k;
		std::cin >> l >> r >> k;
		std::cout << sorted[query(root[l - 1], root[r], 1, maxNumber, k)] << std::endl;
	}

	return 0;
}
