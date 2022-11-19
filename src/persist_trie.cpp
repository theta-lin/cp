// 1333

#include <iostream>
#include <algorithm>

const int maxN(300000);
int trie[maxN * 2 * 24][2];
int end [maxN * 2 * 24];
int sum [maxN * 2];
int root[maxN * 2];
int newNode;

int insert(int index, int pos, int node)
{
	int currentNode(++newNode);
	if (pos < 0)
	{
		end[currentNode] = index;
		return currentNode;
	}

	int digit((sum[index] >> pos) & 1);
	trie[currentNode][digit] = insert(index, pos - 1, trie[node][digit]);
	trie[currentNode][digit ^ 1] = trie[node][digit ^ 1];
	end[currentNode] = std::max(end[trie[currentNode][0]], end[trie[currentNode][1]]);
	return currentNode;
}

int query(int value, int pos, int limit, int node)
{
	int digit((value >> pos) & 1);
	if (pos < 0)
		return sum[end[node]] ^ value;
	if (end[trie[node][digit ^ 1]] >= limit)
		return query(value, pos - 1, limit, trie[node][digit ^ 1]);
	else
		return query(value, pos - 1, limit, trie[node][digit]);
}

int main()
{
	int N, M;
	std::cin >> N >> M;

	end[0] = -1;
	root[0] = insert(0, 23, 0);
	for (int i(1); i <= N; ++i)
	{
		int x;
		std::cin >> x;
		sum[i] = sum[i - 1] ^ x;
		root[i] = insert(i, 23, root[i - 1]);
	}

	for (int i(1); i <= M; ++i)
	{
		char op;
		std::cin >> op;
		if (op == 'A')
		{
			int x;
			std::cin >> x;
			++N;
			sum[N] = sum[N - 1] ^ x;
			root[N] = insert(N, 23, root[N - 1]);
		}
		else
		{
			int l, r, x;
			std::cin >> l >> r >> x;
			std::cout << query(x ^ sum[N], 23, l - 1, root[r - 1]) << '\n';
		}
	}

	return 0;
}
