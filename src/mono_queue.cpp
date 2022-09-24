// 2840

#include <deque>
#include <algorithm>
#include <iostream>

long long sum[2000000 + 10];

int main()
{
	std::ios::sync_with_stdio(false);
	int n, d;
	long long p;
	std::cin >> n >> p >> d;
	for (int i(1); i <= n; ++i)
	{
		int t;
		std::cin >> t;
		sum[i] = sum[i - 1] + t;
	}

	int ans(0);
	std::deque<int> deque;
	for (int i(d), j(0); i <= n; ++i)
	{
		while (!deque.empty() && sum[i] - sum[i - d] > sum[deque.back()] - sum[deque.back() - d])
			deque.pop_back();
		deque.push_back(i);
		while (!deque.empty() && sum[i] - sum[j] - (sum[deque.front()] - sum[deque.front() - d]) > p)
		{
			++j;
			while (!deque.empty() && deque.front() - d < j)
				deque.pop_front();
		}
		ans = std::max(ans, i - j);
	}

	std::cout << ans << std::endl;
	return 0;
}
