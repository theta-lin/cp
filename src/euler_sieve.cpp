#include <iostream>
#include <vector>

const int maxN (1000000);

bool sieve[maxN];
int  mu   [maxN];
int  phi  [maxN];

int main()
{
	mu[1] = 1;
	phi[1] = 1;
	std::vector<int> prime;
	for (int i(2); i < maxN; ++i)
	{
		if (!sieve[i])
		{
			prime.push_back(i);
			mu[i] = -1;
			phi[i] = i - 1;
		}

		for (std::size_t j(0); j < prime.size() && i * prime[j] < maxN; ++j)
		{
			sieve[i * prime[j]] = true;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else
			{
				mu[i * prime[j]] = -mu[i];
				phi[i * prime[j]] = phi[i] * phi[prime[j]];
			}
		}
	}

	for (int i(1); i <= 100; ++i)
		std::cout << phi[i] << ' ';
	std::cout << std::endl;

	return 0;
}
