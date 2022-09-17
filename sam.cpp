#include <cstdio>
#include <cstring>

int n;

const int maxN (50000 + 10);
const int maxCh(256 + 10);
char      str  [maxN];
int       next [maxN * 2][maxCh];
int       link [maxN * 2];
int       len  [maxN * 2];

int lastNode;

void buildSam()
{
	lastNode = 0;
	int last(0);
	link[0] = -1;
	memset(next[0], 0, sizeof(next[0]));

	for (int i(1); i <= n; ++i)
	{
		int cur(++lastNode);
		len[cur] = i;
		memset(next[cur], 0, sizeof(next[cur]));

		int pre(last);
		while (pre != -1 && !next[pre][int(str[i])])
		{
			next[pre][int(str[i])] = cur;
			pre = link[pre];
		}

		if (pre != -1)
		{
			int suc(next[pre][int(str[i])]);
			if (len[suc] == len[pre] + 1)
			{
				link[cur] = suc;
			}
			else
			{
				int clone(++lastNode);
				memcpy(next[clone], next[suc], sizeof(next[clone]));
				link[clone] = link[suc];
				len[clone] = len[pre] + 1;
				link[suc] = clone;

				while (pre != -1 && next[pre][int(str[i])] == suc)
				{
					next[pre][int(str[i])] = clone;
					pre = link[pre];
				}
				link[cur] = clone;
			}
		}
		else
		{
			link[cur] = 0;
		}

		last = cur;
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int ttt(1); ttt <= T; ++ttt)
	{
		scanf("%s", str + 1);
		n = strlen(str + 1);

		buildSam();
		long long ans(0);
		for (int i(1); i <= lastNode; ++i)
		{
			ans += len[i] - len[link[i]];
		}
		printf("%lld\n", ans);
	}

	return 0;
}
