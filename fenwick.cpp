const int maxN(1000000);

long long BIT[maxN];

int lowbit(int x)
{
	return x & (-x);
}

void add(int pos, int value)
{
	while (pos <= maxN)
	{
		BIT[pos] += value;
		pos += lowbit(pos);
	}
}

int get(int pos)
{
	int sum(0);
	while (pos > 0)
	{
		sum += BIT[pos];
		pos -= lowbit(pos);
	}
	return sum;
}
