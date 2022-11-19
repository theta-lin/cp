const int maxBits{32};
int       basis  [maxBits];
bool      failed {false};

void add(int x)
{
	for (int i{maxBits - 1}; i >= 0; --i)
	{
		if ((x >> i) & 1)
		{
			if (basis[i])
			{
				x ^= basis[i];
			}
			else
			{
				basis[i] = x;
				return;
			}
		}
	}

	failed = true;
}

int getMax()
{
	int ans{0};
	for (int i{maxBits - 1}; i >= 0; --i)
	{
		if ((ans ^ basis[i]) > ans) ans ^= basis[i];
	}
	return ans;
}

int getMin()
{
	if (failed) return 0;
	for (int i{0}; i < maxBits; ++i)
	{
		if (basis[i]) return basis[i];
	}
	return -1;
}

void reduce()
{
	for (int i{1}; i < maxBits; ++i)
	{
		for (int j{0}; j < i; ++j)
		{
			if ((basis[i] >> j) & 1) basis[i] ^= basis[j];
		}
	}
}

// Must call reduce() before calling getKth()
int getKth(int k)
{
	if (k == 1 && failed) return 0;
	if (failed) --k;

	int ans{0};
	for (int i{0}; i < maxBits; ++i)
	{
		if (basis[i])
		{
			if (k % 2 == 1) ans ^= basis[i];
			k /= 2;
		}
	}
	return ans;
}
