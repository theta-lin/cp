#include <algorithm>

int *end;
const int maxN(100000);

int a[maxN];

int get(int x)
{
	return std::lower_bound(a, end, x) - a + 1;
}

int main()
{
	int n;
	std::sort(a + 1, a + n + 1);
	end = std::unique(a + 1, a + n + 1);
}
