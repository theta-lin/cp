//1276

#include <cstdio>

const int maxN(2000000 + 10);
long long fact[maxN];

const long long mod(20100403);

long long qPow(long long base, long long expo)
{
	long long prod(1);
	for (long long i(1); i <= expo; i *= 2)
	{
		if (i & expo)
		{
			prod = prod * base % mod;
		}
		base = base * base % mod;
	}
	return prod;
}

long long inv(long long n)
{
	return qPow(n, mod - 2);
}

long long C(long long n, long long m)
{
	if (m > n) return 0;
	return fact[n] * inv(fact[m] * fact[n - m] % mod) % mod;
}

int main()
{
	fact[0] = 1;
	for (int i(1); i < maxN; ++i)
	{
		fact[i] = fact[i - 1] * i % mod;
	}
	long long n, m;
	scanf("%lld %lld", &n, &m);
	if (n < m)
	{
		printf("0\n");
	}
	else
	{
		printf("%lld\n", (C(n + m, n) - C(n + m, m - 1) + mod) % mod);
	}
	return 0;
}
