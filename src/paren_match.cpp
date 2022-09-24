// 4652

#include <cstdio>
#include <vector>

const int        maxN (500000 + 10);
std::vector<int> edge [maxN];
char             in   [maxN];
bool             type [maxN];
int              stack[maxN];
int              match[maxN];
int              cnt  [maxN];
int              cons [maxN];
long long        sum  [maxN];

long long ans(0);

int top(0);

void dfs(int v, int pre)
{
	++top;
	stack[top] = type[v];
	if (type[v] == 0 || stack[pre] == 1)
	{
		match[top] = top;
		cons[top] = 0;
		if (top > 0)
		{
			sum[top] = sum[top - 1];
		}
		else
		{
			sum[top] = 0;
		}
	}
	else
	{
		match[top] = match[pre - 1];
		cons[top] = cons[pre - 1] + 1;
		sum[top] = sum[top - 1] + cons[top];
	}
	ans ^= v * sum[top];

	for (size_t i(0); i < edge[v].size(); ++i)
	{
		dfs(edge[v][i], match[top]);
	}

	--top;
}

int main()
{
	int n;
	scanf("%d", &n);
	scanf("%s", in + 1);
	for (int i(1); i <= n; ++i)
	{
		type[i] = (in[i] == '(' ? 0 : 1);
	}
	for (int i(2); i <= n; ++i)
	{
		int f;
		scanf("%d", &f);
		edge[f].push_back(i);
	}

	stack[0] = 1;
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}
