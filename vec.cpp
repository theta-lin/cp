#include <cmath>

struct Vec
{
	double x;
	double y;

	Vec()
	{
	}

	Vec(double x, double y) : x(x), y(y)
	{
	}

	double norm() const
	{
		return std::sqrt(x * x + y * y);
	}

	Vec normalize() const
	{
		double invNorm(1 / norm());
		return Vec(x * invNorm, y * invNorm);
	}
};

Vec operator+(const Vec &a, const Vec &b)
{
	return Vec(a.x + b.x, a.y + b.y);
}

Vec operator-(const Vec &a, const Vec &b)
{
	return Vec(a.x - b.x, a.y - b.y);
}

Vec operator*(double a, const Vec &b)
{
	return Vec(a * b.x, a * b.y);
}

double dot(const Vec &a, const Vec &b)
{
	return a.x * b.x + a.y * b.y;
}

double cross(const Vec &a, const Vec &b)
{
	return a.x * b.y - a.y * b.x;
}

double xtan2(double y, double x)
{
	double p(x / (std::abs(x) + std::abs(y)));
	return y < 0 ? p - 1 : 1 - p;
}

double diff(const Vec &a, const Vec &b)
{
	static const double pi(std::acos(-1));
	double angle(xtan2(cross(a, b), dot(a, b)));
	return angle >= 0 ? angle : pi * 2 + angle;
}

int quad(const Vec &v)
{
	if (v.x >= 0)
	{
		if (v.y >= 0)
			return 3;
		else
			return 2;
	}
	else
	{
		if (v.y >= 0)
			return 4;
		else
			return 1;
	}
}

bool operator<(const Vec &a, const Vec &b)
{
	Vec da(a - origin), db(b - origin);
	return quad(da) < quad(db) || (quad(da) == quad(db) && cross(da, db) > 0);
}
