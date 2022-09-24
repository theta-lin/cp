#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxN(2000000 + 10);
char      in  [maxN];
char      str [maxN];
int       cnt [maxN];

int main()
{
	scanf("%s", in + 1);
	int len(strlen(in + 1));
	str[0] = '$';
	for (int i(1); i <= len; ++i)
	{
		str[i * 2 - 1] = in[i];
		if (i < len) str[i * 2] = '#';
	}
	len = len * 2 - 1;
	str[len + 1] = '\0';

	int mid(0);
	int r(0);
	for (int i(1); i <= len; ++i)
	{
		if (i <= r)
		{
			cnt[i] = std::min(cnt[mid - (i - mid)], r - i + 1);
		}

		while (str[i - cnt[i]] == str[i + cnt[i]])
		{
			//printf("%c + %d -> %c,%c\n", str[i], cnt[i], str[i - cnt[i]], str[i + cnt[i]]);
			++cnt[i];
		}

		if (i + cnt[i] - 1 > r)
		{
			mid = i;
			r = i + cnt[i] - 1;
		}
	}

	for (int i(1); i <= len; ++i)
	{
		if (str[i] == '#' && cnt[i] == 1)
		{
			cnt[i] = 0;
		}
		if (str[i + cnt[i] - 1] == '#')
		{
			--cnt[i];
		}
		printf("%d ", cnt[i]);
	}
	printf("\n");
	return 0;
}
