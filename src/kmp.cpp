#include <iostream>
#include <fstream>
#include <string>

const int   maxN {1000000};
int         fail [maxN];
int         match[maxN];

void build(std::string &pat)
{
	fail[0] = -1;
	for (int i{1}, j{-1}; i < pat.length(); ++i)
	{
		while (j >= 0 && pat[i] != pat[j + 1]) j = fail[j];
		if (pat[i] == pat[j + 1]) ++j;
		fail[i] = j;
	}
}

int find(std::string &str, std::string &pat)
{
	int cnt{0};
	for (int i{0}, j{-1}; i < str.length(); ++i)
	{
		while (j >= 0 && (j == pat.length() - 1 || str[i] != pat[j + 1]))
		{
			j = fail[j];
		}
		if (str[i] == pat[j + 1]) ++j;
		match[i] = j;
		if (j == pat.length() - 1) ++cnt;
	}
	return cnt;
}

int main()
{
	std::string T{"anana"};
	std::string S{"banananban"};

	build(T);
	find(S, T);

	for (int i{0}; i < T.length(); ++i) std::cout << T[i] << ' ';
	std::cout << std::endl;
	for (int i{0}; i < T.length(); ++i) std::cout << fail[i] << ' ';
	std::cout << std::endl;
	for (int i{0}; i < S.length(); ++i) std::cout << S[i] << ' ';
	std::cout << std::endl;
	for (int i{0}; i < S.length(); ++i) std::cout << match[i] << ' ';
	std::cout << std::endl;

	return 0;
}
