#include <iostream>
#include <string>
#include <cctype>
#include <limits>

std::string str;
int pos(0);
int lookup[256];

bool lessPower(char p0, char p1)
{
	if (p0 == '^' && p1 == '^')
		return true;
	else
		return lookup[p0] < lookup[p1];
}

int parse(char oldOp)
{
	int left(0);
	if (str[pos] == '(')
	{
		++pos;
		left = parse(0);
		++pos;
	}
	else
	{
		while (pos < str.size() && isdigit(str[pos]))
		{
			left = left * 10 + static_cast<int>(str[pos] - '0');
			++pos;
		}
	}

	while (pos < str.size() && str[pos] != ')' && !isdigit(str[pos]) && lessPower(oldOp, str[pos]))
	{
		char op(str[pos]);
		++pos;
		int right(parse(op));
		switch (op)
		{
		case '+':
			left += right;
			break;

		case '-':
			left -= right;
			break;

		case '*':
			left *= right;
			break;

		case '/':
			left /= right;
			break;

		case '^':
			{
				int temp(left);
				left = 1;
				for (int i(0); i < right; ++i)
					left *= temp;
			}
			break;

		default:
			break;
		}
	}

	return left;
}

int main()
{
	lookup[0]   = 0;
	lookup['+'] = 1;
	lookup['-'] = 1;
	lookup['*'] = 2;
	lookup['/'] = 2;
	lookup['^'] = 3;
	std::cin >> str;
	std::cout << parse(0) << std::endl;
	return 0;
}
