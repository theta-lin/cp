long long qpow(long long base, long long ex)
{
	long long prod(1);
	for (long long i(1); i <= ex; i *= 2)
	{
		if (i & ex) prod = prod * base % mod;
		base = base * base % mod;
	}
	return prod;
}

long long inv(long long n)
{
	return qpow(n, mod - 2);
}

long long C(long long n, long long m)
{
	return fact[n] * inv(fact[m] * fact[n - m] % mod) % mod;
}
