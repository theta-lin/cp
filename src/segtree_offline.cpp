// 1677

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <list>

std::map<std::pair<int, int>, int> t;
std::list<std::pair<int, int> >    link  [200000 * 4 + 10];
std::pair<int, int>                query [200000     + 10];
int                                result[200000     + 10];
int                                father[10000 + 10];
int                                size  [10000 + 10];

int read()
{
	char ch;
	do ch = getchar();
	while (ch < '0' || ch > '9');

	int ret(0);
	while (ch >= '0' && ch <= '9')
	{
		ret = ret * 10 + static_cast<int>(ch - '0');
		ch = getchar();
	}
	return ret;
}

char readCmd()
{
	char ch;
	do ch = getchar();
	while (ch < 'A' || ch > 'Z');
	return ch;
}

void insert(int node, int left, int right, int oLeft, int oRight, const std::pair<int, int> &pair)
{
	//printf("%d %d %d %d\n", left, right, oLeft, oRight);
	//system("pause");
	if (left >= oLeft && right <= oRight)
	{
		link[node].push_back(pair);
		return;
	}

	int mid((left + right) / 2);
	if (oLeft <= mid)
		insert(node * 2, left, mid, oLeft, oRight, pair);
	if (oRight > mid)
		insert(node * 2 + 1, mid + 1, right, oLeft, oRight, pair);
}

int getFather(int index)
{
	while (father[index] != index)
		index = father[index];
	return index;
}

void simulate(int node, int left, int right, std::list<std::pair<int, int> >::iterator it)
{
	//printf("%d %d\n", left, right);
	int fa1, fa2;
	bool sameTree(true);
	if (it != link[node].end())
	{
		fa1 = getFather(it->second);
		fa2 = getFather(it->first);
		sameTree = (fa1 == fa2);
	}
	if (!sameTree)
	{
		if (size[fa1] < size[fa2])
			std::swap(fa1, fa2);
		father[fa2] = fa1;
  		size[fa1] += size[fa2];
	}

	if (it != link[node].end() && ++it != link[node].end())
	{
		simulate(node, left, right, it);
	}
	else if (left < right)
	{
		int mid((left + right) / 2);
		simulate(node * 2, left, mid, link[node * 2].begin());
		simulate(node * 2 + 1, mid + 1, right, link[node * 2 + 1].begin());
	}
	else if (query[left].first != 0)
	{
		//printf("%d %d\n", getFather(query[left].first), getFather(query[left].second));
		result[left] = (getFather(query[left].first) == getFather(query[left].second));
	}

	if (!sameTree)
	{
		father[fa2] = fa2;
		size[fa1] -= size[fa2];
	}
}

int main()
{
	int n(read()), m(read());
	for (int i(1); i <= m; ++i)
	{
		char cmd(readCmd());
		std::pair<int, int> pair;
		pair.first = read();
		pair.second = read();
		if (pair.first > pair.second)
			std::swap(pair.first, pair.second);
		if (cmd == 'C')
		{
			t[pair] = i;
		}
		else if (cmd == 'D')
		{
			insert(1, 1, m, t[pair], i, pair);
			t[pair] = 0;
		}
		else
		{
			query[i] = pair;
		}
	}

	for (std::map<std::pair<int, int>, int>::iterator it(t.begin()); it != t.end(); ++it)
	{
		if (it->second != 0)
			insert(1, 1, m, it->second, m, it->first);
	}

	memset(result, -1, sizeof(result));
	for (int i(1); i <= n; ++i)
	{
		father[i] = i;
		size[i] = 1;
	}
	simulate(1, 1, m, link[1].begin());

	for (int i(1); i <= m; ++i)
	{
		if (result[i] == 0)
			printf("No\n");
		else if (result[i] == 1)
			printf("Yes\n");
	}
	return 0;
}
