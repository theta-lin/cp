#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <iostream>
#include <vector>

const int maxN   (10000000 + 10);
const int maxM   (100000 + 10);
const int maxLen (100 + 10);
const int maxCh  (256);
int       map    [maxCh];
char      in     [maxN];
int       orig   [maxN];
int       pattern[maxM][maxLen];
int       len    [maxM];
int       child  [maxN][5];
int       fail   [maxN];
bool      matched[maxN];

std::vector<int> sorted;

int N, M;

int lastNode(0);
void insert(int index)
{
	for (int i(1), node(0); i <= len[index]; ++i)
	{
		int &ch(child[node][pattern[index][i]]);
		if (!ch)
		{
			ch = ++lastNode;
		}
		node = ch;
	}
}

void build()
{
	std::queue<int> queue;
	queue.push(0);

	while (!queue.empty())
	{
		int node(queue.front());
		queue.pop();
		sorted.push_back(node);

		for (int i(1); i <= 4; ++i)
		{
			int &ch(child[node][i]);
			if (ch)
			{
				if (node)
				{
					fail[ch] = child[fail[node]][i];
				}
				queue.push(ch);
			}
			else
			{
				ch = child[fail[node]][i];
			}
		}
	}
}

void match()
{
	for (int i(1), node(0); i <= N; ++i)
	{
		node = child[node][orig[i]];
		matched[node] = true;
	}

	for (int i(lastNode); i >= 0; --i)
	{
		int node(sorted[i]);
		matched[fail[node]] = (matched[fail[node]] || matched[node]);
	}
}

int main()
{
	map[int('E')] = 1;
	map[int('S')] = 2;
	map[int('W')] = 3;
	map[int('N')] = 4;

	scanf("%d %d", &N, &M);
	scanf("%s", in + 1);
	for (int i(1); i <= N; ++i)
	{
		orig[i] = map[int(in[i])];
	}
	for (int i(1); i <= M; ++i)
	{
		scanf("%s", in + 1);
		len[i] = strlen(in + 1);
		for (int j(1); j <= len[i]; ++j)
		{
			pattern[i][j] = map[int(in[j])];
		}
		insert(i);
	}

	build();
	match();

	for (int i(1); i <= M; ++i)
	{
		int ans(0);
		int node(0);
		//printf("%d: ", i);
		for (int j(1); j <= len[i]; ++j)
		{
			node = child[node][pattern[i][j]];
			//printf("%d ", matched[node]);
			if (matched[node])
			{
				ans = j;
			}
		}
		//printf("\n");
		printf("%d\n", ans);
	}

	return 0;
}
