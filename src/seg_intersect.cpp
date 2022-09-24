// 2470

#include <cstdio>
#include <utility>
#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstdlib>

struct Vec
{
	long long x;
	long long y;
};

Vec operator-(const Vec &a, const Vec &b)
{
	Vec t = {a.x - b.x, a.y - b.y};
	return t;
}

long long cross(const Vec &a, const Vec &b)
{
	return a.x * b.y - a.y * b.x;
}

const int maxN(100010);
typedef std::pair<Vec, Vec>  Seg;
typedef std::pair<int, bool> EndPoint;
typedef std::set<int>::iterator It;
Seg      seg     [maxN    ];
EndPoint endpoint[maxN * 2];

bool cmpEndpoint(const EndPoint &a, const EndPoint &b)
{
	Vec p1(a.second == 0 ? seg[a.first].first : seg[a.first].second);
	Vec p2(b.second == 0 ? seg[b.first].first : seg[b.first].second);
	//std::cout << '!' << p1.x << ' ' << p2.x  << '\n';
	if (p1.x != p2.x)
		return p1.x < p2.x;
	else if (a.second != b.second)
		return a.second < b.second;
	else
		return p1.y < p2.y;
}

bool intersect(int a, int b)
{
	if (a == b)
	{
		//std::cout << seg[endpoint[ttt].first].first.x << ',' << seg[endpoint[ttt].first].first.y << ' '
		//          << seg[endpoint[ttt].first].second.x << ',' << seg[endpoint[ttt].first].second.y << '\n';
  		std::cout << "WTF?\n";
  	}

	long long d1(cross(seg[a].first - seg[b].first, seg[b].second - seg[b].first));
	long long d2(cross(seg[a].second - seg[b].first, seg[b].second - seg[b].first));
	long long d3(cross(seg[b].first - seg[a].first, seg[a].second - seg[a].first));
	long long d4(cross(seg[b].second - seg[a].first, seg[a].second - seg[a].first));

	//std::cout << "XXX " << d1 << ' ' << d2 << ' ' << d3 << ' ' << d4 << '\n';
	if (((d1 >= 0 && d2 <= 0) || (d1 <= 0 && d2 >= 0)) && ((d3 >= 0 && d4 <= 0) || (d3 <= 0 && d4 >= 0)))
	{
		if (a > b) std::swap(a, b);
		printf("%d %d\n", a, b);
		return true;
	}
	else
	{
		return false;
	}
}

bool cmpSeg(int a, int b)
{
	if (a == b)
		return false;
	if (intersect(a, b))
		exit(0);

	if (seg[a].first.x < seg[b].first.x)
	{
		return cross(seg[a].first - seg[b].first, seg[a].second - seg[b].first) >= 0;
	}
	else
	{
		return cross(seg[b].first - seg[a].first, seg[b].second - seg[a].first) < 0;
	}
}

std::set<int, bool(*)(int, int)> set(cmpSeg);

int main()
{
	int n;
	scanf("%d", &n);
	for (int i(1); i <= n; ++i)
	{
		scanf("%lld %lld %lld %lld", &seg[i].first.x, &seg[i].first.y, &seg[i].second.x, &seg[i].second.y);
		if (seg[i].first.x > seg[i].second.x) std::swap(seg[i].first, seg[i].second);
		endpoint[i * 2 - 1] = std::make_pair(i, 0);
		endpoint[i * 2] = std::make_pair(i, 1);
	}
	std::sort(endpoint + 1, endpoint + n * 2 + 1, cmpEndpoint);

	for (int i(1); i <= n * 2; ++i)
	{
		//std::cout << i << ' ' << endpoint[i].first << ' ' << endpoint[i].second << '\n';
		if (endpoint[i].second == 0)
		{
			set.insert(endpoint[i].first);
		}
		else
		{
			It it(set.find(endpoint[i].first));
			if (it == set.end())
				continue;
			It pre(it);
			set.erase(it);
			if (pre != set.begin())
			{
				--pre;
				It suc(pre);
				++suc;
				//if (pre == suc)
				//	std::cout << "XXX\n";
				if (suc != set.end())
				{
					if (intersect(*pre, *suc))
						return 0;
				}
			}
		}
	}

	return 0;
}
