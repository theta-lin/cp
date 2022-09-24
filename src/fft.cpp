// 1839

#include <iostream>
#include <complex>
#include <iomanip>

std::complex<double> q      [400000 + 10];
std::complex<double> qRev   [400000 + 10];
std::complex<double> g      [400000 + 10];
std::complex<double> denom  [400000 + 10];
int                  reverse[400000 + 10];
const double pi(std::acos(-1.0));

int init(int len)
{
	len *= 2;
	int bitCount(0);
	int limit(1);
	while (limit < len)
	{
		++bitCount;
		limit *= 2;
	}
	for (int i(0); i < limit; ++i)
		reverse[i] = (reverse[i >> 1] >> 1) | ((i & 1) << (bitCount - 1));
	return limit;
}

void FFT(std::complex<double> a[], int len, int inv)
{
	for (int i(0); i < len; ++i)
	{
		if (i < reverse[i])
			std::swap(a[i], a[reverse[i]]);
	}

	for (int half(1); half < len; half *= 2)
	{
		std::complex<double> wn(std::cos(pi / half), inv * std::sin(pi / half));
		for (int i(0); i < len; i += half * 2)
		{
			std::complex<double> w(1.0, 0.0);
			for (int j(0); j < half; ++j)
			{
				std::complex<double> x(a[i + j]);
				std::complex<double> y(w * a[i + half + j]);
				a[i + j] = x + y;
				a[i + half + j] = x - y;
				w *= wn;
			}
		}
	}
}

void FFT(std::complex<double> a[], int len)
{
	FFT(a, len, 1);
}

void invFFT(std::complex<double> a[], int len)
{
	FFT(a, len, -1);
	double invLen(1.0 / len);
	for (int i(0); i < len; ++i)
		a[i] *= invLen;
}

int main()
{
	int n;
	std::cin >> n;
	int limit(init(n));
	for (int i(0); i < n; ++i)
	{
		std::cin >> q[i];
		qRev[n - i - 1] = q[i];
		if (i != 0)
			g[i] = 1.0 / i / i;
	}
	FFT(q, limit);
	FFT(qRev, limit);
	FFT(g, limit);
	for (int i(0); i < limit; ++i)
	{
		q[i] *= g[i];
		qRev[i] *= g[i];
	}
	invFFT(q, limit);
	invFFT(qRev, limit);

	for (int i(0); i < n; ++i)
		std::cout << std::fixed << std::setprecision(3) << q[i].real() - qRev[n - i - 1].real() << std::endl;

	return 0;
}
