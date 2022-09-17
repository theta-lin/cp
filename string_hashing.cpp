#include <iostream>
#include <string>
#include <algorithm>

const int          maxLen(100000 + 10);
unsigned long long hashA;
unsigned long long hashB [maxLen];
unsigned long long weight[maxLen];

int main()
{
	//freopen("string.in", "r", stdin);
	//freopen("string.out", "w", stdout);

	std::ios::sync_with_stdio(false);
	weight[0] = 1;
	for (int i(1); i < maxLen; ++i)
	{
		weight[i] = weight[i - 1] * 31;
	}

	std::string a, b;
	std::cin >> a >> b;
	bool swap(false);
	if (a.length() < b.length())
	{
		std::swap(a, b);
		swap = true;
	}
	std::size_t delta(a.length() - b.length());

	for (std::size_t i(0); i < a.length(); ++i)
	{
		hashA += (a[i] - 'a') * weight[i];
	}
	for (std::size_t i(0); i < a.length(); ++i)
	{
		hashB[0] += (b[i % b.length()] - 'a') * weight[i];
	}
	//printf("0:%llu\n", hashB[0]);
	for (std::size_t i(1); i < b.length(); ++i)
	{
		hashB[i] = hashB[i - 1];
		hashB[i] -= (b[(b.length() + delta - i) % b.length()] - 'a') * weight[b.length() - 1];
		hashB[i] *= 31;
		hashB[i] += (b[b.length() - i] - 'a');
		//printf("%zu:%llu %llu\n", i, hashB[i], (b.length() + delta - i) % b.length());
	}
	//printf("\n");


	std::size_t i(0);
	do
	{
		//printf("%zu:%llu %llu\n", i, hashA, hashB[i]);
		if (hashA != hashB[i])
		{
			for (std::size_t j(0); j < a.length(); ++j)
			{
				std::size_t bj((j + b.length() - i) % b.length());
				//printf("(%c%c)", a[j], b[bj]);
				char ac(a[j]), bc(b[bj]);
				if (swap) std::swap(ac, bc);
				if (ac < bc)
				{
					std::cout << "<\n";
					return 0;
				}
				else if (ac > bc)
				{
					std::cout << ">\n";
					return 0;
				}
			}
			break;
		}
		//printf("\n");

		i = (b.length() - (a.length() - i) % b.length()) % b.length();
	}
	while (i != 0);

	std::cout << "=\n";
	return 0;
}
