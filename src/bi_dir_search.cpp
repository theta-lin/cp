#include <iostream>
#include <algorithm>

int N, M;
int p     [40 + 10];
int first [(1 << 20) + 10];
int firstLen;
int second[(1 << 20) + 10];
int secondLen;

void dfs(int pos, int end, int sum, int dst[], int &len)
{
	if (pos == end)
	{
		dst[len++] = sum;
	}
	else
	{
		dfs(pos + 1, end, sum, dst, len);
		if (sum + p[pos] <= M)
			dfs(pos + 1, end, sum + p[pos], dst, len);
	}
}

int main()
{
	std::cin >> N >> M;
	for (int i(0); i < N; ++i)
		std::cin >> p[i];

	dfs(0, N / 2, 0, first, firstLen);
	dfs(N / 2, N, 0, second, secondLen);

	std::sort(first, first + firstLen, std::greater<int>());
	std::sort(second, second + secondLen);

	int ans(0);
	for (int i(0), j(0); i < firstLen; ++i)
	{
		while (j < secondLen - 1 && first[i] + second[j + 1] <= M)
			++j;
		ans = std::max(ans, first[i] + second[j]);
	}
	std::cout << ans << std::endl;
	return 0;
}
