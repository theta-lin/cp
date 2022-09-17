// 1363

#include <cstdio>
#include <algorithm>

struct Frac
{
	int y;
	int x;

	Frac() : y(0), x(1)
	{
	}

	Frac(int y, int x) : y(y), x(x)
	{
	}
};

bool operator<(const Frac &a, const Frac &b)
{
	return 1ll * a.y * b.x - 1ll * b.y * a.x < 0;
}

bool operator==(const Frac &a, const Frac &b)
{
	return 1ll * a.y * b.x - 1ll * b.y * a.x == 0;
}

bool operator<=(const Frac &a, const Frac &b)
{
	return a < b || a == b;
}

const int maxN(100000 + 10);
Frac      a   [maxN * 4];
Frac      max [maxN * 4];
int       ans [maxN * 4];

int pushUp(int node, int tl, int tr, const Frac &f)
{
	if (max[node] <= f)
	{
		return 0;
	}
	else if (f < a[tl])
	{
		return ans[node];
	}
	else
	{
		int mid((tl + tr) / 2);
		if (max[node * 2] < f)
		{
			return pushUp(node * 2 + 1, mid + 1, tr, f);
		}
		else
		{
			return pushUp(node * 2, tl, mid, f) + ans[node] - ans[node * 2];
		}
	}
}

void insert(int node, int tl, int tr, const Frac &f)
{
	if (tl == tr)
	{
		a[tl] = f;
		max[node] = f;
		ans[node] = 1;
	}
	else
	{
		int mid((tl + tr) / 2);
		if (f.x <= mid) insert(node * 2, tl, mid, f);
		else insert(node * 2 + 1, mid + 1, tr, f);
		max[node] = std::max(max[node * 2], max[node * 2 + 1]);
		ans[node] = ans[node * 2] + pushUp(node * 2 + 1, mid + 1, tr, max[node * 2]);
	}
}

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	for (int i(1); i <= M; ++i)
	{
		Frac f;
		scanf("%d %d", &f.x, &f.y);
		insert(1, 1, N, f);
		printf("%d\n", ans[1]);
	}

	return 0;
}
