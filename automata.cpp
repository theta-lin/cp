// 5201

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

int       lastNode  (0);
int       lastEdge  (0);
const int maxN      (1000000 + 10);
int       patternLen;
int       to        [maxN];
int       trans     [maxN];
int       pre       [maxN];
int       last      [maxN];
char      pattern   [maxN];
char      s         [maxN];

void addEdge(int u, int v, int t)
{
	++lastEdge;
	to[lastEdge] = v;
	trans[lastEdge] = t;
	pre[lastEdge] = last[u];
	last[u] = lastEdge;
}

void addEdge(std::vector<int> &u, int v, int t)
{
	for (std::size_t i(0); i < u.size(); ++i)
	{
		addEdge(u[i], v, t);
	}
}

int build(int pred, int pos)
{
	std::vector<int> branch;
	while (pos <= patternLen && pattern[pos] != ']')
	{
		switch (pattern[pos])
		{
		case 'N':
		case 'S':
		case 'E':
		case 'W':
			++lastNode;
			addEdge(pred, lastNode, pattern[pos]);
			addEdge(branch, lastNode, pattern[pos]);
			branch.clear();
			pred = lastNode;
			break;

		case '*':
			++lastNode;
			addEdge(pred, lastNode, 0);
			addEdge(branch, lastNode, 0);
			addEdge(lastNode, lastNode, 0);
			branch.clear();
			branch.push_back(lastNode);
			break;

		case '?':
			++lastNode;
			addEdge(pred, lastNode, 0);
			addEdge(branch, lastNode, 0);
			branch.clear();
			pred = lastNode;
			break;

		case '[':
			pos = build(pred, pos + 1);
			branch.push_back(lastNode);
			break;

		case '\0':
			++lastNode;
			addEdge(pred, 2, 0);
			addEdge(branch, 2, 0);
			break;

		default:
			break;
		}

		++pos;
	}

	return pos;
}

int main()
{
	scanf("%s", pattern);
	patternLen = strlen(pattern);
	++lastNode; // S: 1
	++lastNode; // T: 2
	build(1, 0);

	int n;
	scanf("%d", &n);
	for (int i(1); i <= n; ++i)
	{
		scanf("%s", s);
		int len(strlen(s));
		std::vector<int> queue;
		queue.push_back(1);
		for (int j(0); j <= len + 1; ++j)
		{
			bool can(false);
			std::vector<int> tmp;
			for (std::size_t k(0); k < queue.size(); ++k)
			{
				if (queue[k] == 2)
				{
					can = true;
				}
				for (int e(last[queue[k]]); e; e = pre[e])
				{
					if (!trans[e] || trans[e] == s[j])
					{
						tmp.push_back(to[e]);
					}
				}
			}

			std::sort(tmp.begin(), tmp.end());
			tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
			std::swap(queue, tmp);

			if (j > 1)
			{
				printf(can ? "1" : "0");
			}
		}
		printf("\n");
	}

	return 0;
}
