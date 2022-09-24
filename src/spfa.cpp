#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

int       start[20 + 10];
int       to            [400000 + 10];
int       pre           [400000 + 10];
long long len           [400000 + 10];
int       last          [100000 + 10];
long long dist [20 + 10][100000 + 10];
long long minDist       [100000 + 10];
bool      far           [100000 + 10];
bool      in            [100000 + 10];
bool      dp            [1 << 20];

int n, m, k;
const long long maxByte(0x30);
const long long mod(998244353);
std::queue<int> queue;

void spfa(int origin, long long d[100000 + 10])
{
	d[origin] = 0;
	queue.push(origin);
	in[origin] = true;
	while (!queue.empty())
	{
		for (int i(last[queue.front()]); i != 0; i = pre[i])
		{
			if (d[to[i]] > d[queue.front()] + len[i])
			{
				d[to[i]] = d[queue.front()] + len[i];
				if (!in[to[i]])
				{
					queue.push(to[i]);
					in[to[i]] = true;
				}
			}
		}

		in[queue.front()] = false;
		queue.pop();
	}
}

int main()
{
	std::cin >> n >> m >> k;
	for (int i(0); i < k; ++i)
		std::cin >> start[i];

	for (int i(1); i <= m; ++i)
	{
		int x, y, l;
		std::cin >> x >> y >> l;
		to[i * 2 - 1] = y;
		len[i * 2 - 1] = l;
		pre[i * 2 - 1] = last[x];
		last[x] = i * 2 - 1;

		to[i * 2] = x;
		len[i * 2] = l;
		pre[i * 2] = last[y];
		last[y] = i * 2;
	}

	memset(minDist, maxByte, sizeof(minDist));
	for (int i(0); i < k; ++i)
	{
		memset(dist[i], maxByte, sizeof(dist[i]));
		spfa(start[i], dist[i]);
		for (int j(1); j <= n; ++j)
			minDist[j] = std::min(minDist[j], dist[i][j]);
	}

	/*for (int i(0); i < k; ++i)
	{
		for (int j(1); j <= n; ++j)
			std::cout << dist[i][j] << ' ';
		std::cout << std::endl;
	}// */

	long long max(0);
	for (int j(1); j <= n; ++j)
		max = std::max(max, minDist[j]);
	for (int j(1); j <= n; ++j)
	{
		int state(0);
		for (int i(0); i < k; ++i)
		{
			if (dist[i][j] <= max)
				state |= 1 << i;
		}
		dp[state] = true;
		//std::cout << state << std::endl;
	}

	int count(0);
	for (int i(0); i < (1 << k); ++i)
	{
		if (dp[i])
			++count;
		for (int j(0); j < k; ++j)
			dp[i | (1 << j)] = dp[i | (1 << j)] || dp[i];
	}

	long long base(1 << k), power(mod - 2);
	long long denom(1);
	for (long long i(1), mult(base); i <= power; i *= 2, mult = mult * mult % mod)
	{
		if (power & i)
			denom = denom * mult % mod;
	}

	//std::cout << count << std::endl;
	std::cout << ((1 << k) - count) * denom % mod << std::endl;
	return 0;
}
