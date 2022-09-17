// 5237

#include <cstdio>
#include <bitset>
#include <cstdlib>

int n, m;

const int maxN(9);

const int mod(10000007);

struct Bitset
{
	std::bitset<maxN * maxN> bs;
	std::bitset<maxN * maxN>::reference operator()(int x, int y)
	{
		return bs[x * m + y];
	}
	bool operator()(int x, int y) const
	{
		return bs[x * m + y];
	}

	const std::bitset<maxN * maxN>& data() const
	{
		return bs;
	}

	int hash() const
	{
		int h(0);
		int cur(1);
		for (int i(0); i < maxN * maxN; ++i)
		{
			if (bs[i])
			{
				h = (h + cur) % mod;
			}
			cur = cur * 2 % mod;
		}
		return h;
	}
};

bool      used  [mod];
Bitset    belong[mod];
long long mem   [mod];

int hashFind(const Bitset &bs)
{
	int pos(bs.hash());
	while (used[pos] && belong[pos].data() != bs.data())
	{
		pos = (pos + 1) % mod;
	}
	if (!used[pos])
	{
		belong[pos] = bs;
	}
	return pos;
}

char in   [maxN + 10];

const int typeCnt(14);
int       dx     [typeCnt][4] = {
									{0,  1,  2,  3},
									{0,  0,  0,  0},
									{0,  0,  1,  2},
									{0,  1,  1,  1},
									{0,  1,  2,  2},
									{0,  0,  0,  1},
									{0,  0,  1,  2},
									{0,  0,  0,  1},

									{0,  1,  2,  2},
									{0,  1,  1,  1},
									{0,  1,  1,  1},
									{0,  1,  1,  2},
									{0,  0,  0,  1},
									{0,  1,  1,  2}
                                };
int       dy     [typeCnt][4] = {
									{0,  0,  0,  0},
									{0,  1,  2,  3},
									{0,  1,  1,  1},
									{0,  0, -1, -2},
									{0,  0,  0,  1},
									{0,  1,  2,  0},
									{0,  1,  0,  0},
									{0,  1,  2,  2},

									{0,  0,  0, -1},
									{0,  0,  1,  2},
									{0, -1,  0,  1},
									{0,  0,  1,  0},
									{0,  1,  2,  1},
									{0, -1,  0,  0}
                                };

bool can(const Bitset &bs, int x, int y, int type)
{
	for (int i(0); i < 4; ++i)
	{
		int xp(x + dx[type][i]), yp(y + dy[type][i]);
		if (xp < 0 || xp >= n || yp < 0 || yp >= m || bs(xp, yp))
		{
			return false;
		}
	}
	return true;
}

void toggle(Bitset &bs, int x, int y, int type)
{
	for (int i(0); i < 4; ++i)
	{
		int xp(x + dx[type][i]), yp(y + dy[type][i]);
		bs(xp, yp) = !bs(xp, yp);
	}
}

void find(const Bitset &bs, int x, int y, int &xp, int &yp)
{
	xp = x;
	yp = y;
	while (xp < n && bs(xp, yp))
	{
		//printf("$$$$$$ %d, %d\n", xp, yp);
		if (yp < m - 1)
		{
			++yp;
		}
		else
		{
			yp = 0;
			++xp;
		}
	}
}

long long dfs(const Bitset &state, int x, int y)
{
	/*printf("!%d, %d\n", x, y);
	for (int i(0); i < n; ++i)
	{
		for (int j(0); j < m; ++j)
		{
			printf("%d", int(state(i, j)));
		}
		printf("\n");
	}
	printf("\n");
	system("pause");//*/

	int id(hashFind(state));
	//printf("%d\n", id);

	if (used[id])
	{
		return mem[id];
	}

	used[id] = true;

	if (x == n)
	{
		//printf("!!!!!! %d\n", int(state.data().count()));
		mem[id] = (int(state.data().count()) == n * m);
	}
	else
	{

		for (int i(0); i < typeCnt; ++i)
		{
			Bitset cur(state);
			if (can(cur, x, y, i))
			{
				toggle(cur, x, y, i);
				int xp, yp;
				find(cur, x, y, xp, yp);
				mem[id] += dfs(cur, xp, yp);
			}
		}
	}

	return mem[id];
}

int main()
{
	/*n = 4;
	m = 8;
	for (int i(0); i < typeCnt; ++i)
	{
		Bitset bs;
		toggle(bs, 0, m / 2 - 1, i);
		printf("***%d***\n", i);
		for (int j(0); j < n; ++j)
		{
			for (int k(0); k < m; ++k)
			{
				printf("%d", int(bs(j, k)));
			}
			printf("\n");
		}
		printf("\n");
	} //*/

	scanf("%d %d", &n, &m);
	Bitset empty;
	for (int i(0); i < n; ++i)
	{
		scanf("%s", in);
		for (int j(0); j < m; ++j)
		{
			empty(i, j) = (in[j] == '*');
		}
	}

	int x, y;
	find(empty, 0, 0, x, y);
	printf("%lld\n", dfs(empty, x, y));
	return 0;
}
