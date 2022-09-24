// 4658

#include <cstdio>
#include <map>
#include <vector>

const int maxPre(10000000);
bool      sieve [maxPre];
long long phiPre[maxPre];
long long muPre [maxPre];

std::map<int, long long> phiSum;
std::map<int, long long> muSum;

long long getPhiSum(long long n)
{
	if (n < maxPre) return phiPre[n];
	if (phiSum.count(n)) return phiSum[n];

	phiSum[n] = 1ll * n * (n + 1) / 2;
	for (long long l(2), r; l <= n; l = r + 1)
	{
		r = n / (n / l);
		phiSum[n] -= (r - l + 1) * getPhiSum(n / l);
	}
	return phiSum[n];
}

long long getMuSum(int n)
{
	if (n < maxPre) return muPre[n];
	if (muSum.count(n)) return muSum[n];

	muSum[n] = 1;
	for (long long l(2), r; l <= n; l = r + 1)
	{
		r = n / (n / l);
		muSum[n] -= (r - l + 1) * getMuSum(n / l);
	}
	return muSum[n];
}

int main()
{
	phiPre[1] = 1;
	muPre[1] = 1;
	std::vector<long long> prime;
	for (int i(2); i < maxPre; ++i)
	{
		if (!sieve[i])
		{
			phiPre[i] = i - 1;
			muPre[i] = -1;
			prime.push_back(i);
		}

		for (std::size_t j(0); j < prime.size() && i * prime[j] < maxPre; ++j)
		{
			sieve[i * prime[j]] = true;
			if (i % prime[j] == 0)
			{
				phiPre[i * prime[j]] = phiPre[i] * prime[j];
				muPre[i * prime[j]] = 0;
				break;
			}
			else
			{
				phiPre[i * prime[j]] = phiPre[i] * phiPre[prime[j]];
				muPre[i * prime[j]] = -muPre[i];
			}
		}
	}

	for (int i(2); i < maxPre; ++i)
	{
		phiPre[i] += phiPre[i - 1];
		muPre[i] += muPre[i - 1];
	}

	int T;
	scanf("%d", &T);
	for (int ttt(1); ttt <= T; ++ttt)
	{
		int N;
		scanf("%d", &N);
		printf("%lld %lld\n", getPhiSum(N), getMuSum(N));
	}

	return 0;
}
