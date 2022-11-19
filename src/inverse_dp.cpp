#include <cstdio>

const int       maxN(2000000 + 10);
const long long mod (1000000007);
long long       inv [maxN];

int main()
{
	int n;
	scanf("%d", &n);

	inv[1] = 1;
	for (int i(2); i <= n; ++i)
	{
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	}

	return 0;
}
