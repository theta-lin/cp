// 5145

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <stack>
#include <bitset>
#include <queue>

struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
	char buf[MAXSIZE], *p1, *p2;
	char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
	IO() : p1(buf), p2(buf), pp(pbuf) {}
	~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
	inline char gc() {
#if DEBUG
		return getchar();
#endif
		if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
		return p1 == p2 ? ' ' : *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	template <class T>
		inline void read(T &x) {
			register double tmp = 1;
			register bool sign = 0;
			x = 0;
			register char ch = gc();
			for (; !isdigit(ch); ch = gc())
				if (ch == '-') sign = 1;
			for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
			if (ch == '.')
				for (ch = gc(); isdigit(ch); ch = gc())
					tmp /= 10.0, x += tmp * (ch - '0');
			if (sign) x = -x;
		}
	inline void read(char *s) {
		register char ch = gc();
		for (; blank(ch); ch = gc())
			;
		for (; !blank(ch); ch = gc()) *s++ = ch;
		*s = 0;
	}
	inline void read(char &c) {
		for (c = gc(); blank(c); c = gc())
			;
	}
	inline void push(const char &c) {
#if DEBUG
		putchar(c);
#else
		if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
		*pp++ = c;
#endif
	}
	template <class T>
		inline void write(T x) {
			if (x < 0) x = -x, push('-');
			static T sta[35];
			T top = 0;
			do {
				sta[int(top++)] = x % 10, x /= 10;
			} while (x);
			while (top) push(sta[int(--top)] + '0');
		}
	template <class T>
		inline void write(T x, char lastChar) {
			write(x), push(lastChar);
		}
} io;

const int         maxN   (2000 + 10);
int               n;
int               lastDfn(0);
int               lastDcc(0);
double            A      [maxN][maxN];
double            E      [maxN][maxN];
bool              adj    [maxN][maxN];
int               dfn    [maxN];
int               low    [maxN];
std::stack<int>   stack;
int               dcc    [maxN];
int               size   [maxN];
int               edge   [maxN][maxN];
int               in     [maxN];
std::bitset<maxN> connect[maxN];

void tarjan(int v)
{
	dfn[v] = low[v] = ++lastDfn;
	stack.push(v);

	for (int to(1); to <= n; ++to)
	{
		if (adj[v][to] && !dcc[to])
		{
			if (!dfn[to])
			{
				tarjan(to);
			}
			low[v] = std::min(low[v], low[to]);
		}
	}

	//printf("TARJAN %d: %d %d\n", v, dfn[v], low[v]);
	if (dfn[v] == low[v])
	{
		++lastDcc;
		bool done(false);
		while (!done)
		{
			dcc[stack.top()] = lastDcc;
			++size[lastDcc];
			if (stack.top() == v) done = true;
			stack.pop();
		}
	}
}

int main()
{
	//freopen("matrix.in", "r", stdin);

	io.read(n);
	for (int i(1); i <= n; ++i)
	{
		E[i][i] = 1;
	}
	for (int i(1); i <= n; ++i)
	{
		for (int j(1); j <= n; ++j)
		{
			io.read(A[i][j]);
			A[i][j] = E[i][j] - A[i][j];
			if (i != j)
			{
				adj[i][j] = (std::abs(A[i][j]) > 1e-9);
				/*if (std::abs(A[i][j]) > 1e-9)
				{
					printf("%d %d\n", i, j);
				}//*/
			}
		}
	}

	for (int v(1); v <= n; ++v)
	{
		if (!dcc[v])
		{
			tarjan(v);
		}
		//printf("%d: %d\n", v, dcc[v]);
	}

	for (int v(1); v <= n; ++v)
	{
		for (int to(1); to <= n; ++to)
		{
			if (dcc[v] != dcc[to] && adj[v][to] && !edge[dcc[to]][dcc[v]])
			{
				edge[dcc[to]][dcc[v]] = true;
				++in[dcc[v]];
			}
		}
	}

	std::queue<int> queue;
	for (int v(1); v <= lastDcc; ++v)
	{
		//printf("%d ", in[v]);
		connect[v][v] = 1;
		if (in[v] == 0)
		{
			queue.push(v);
		}
	}
	//printf("\n");

	while (!queue.empty())
	{
		int v(queue.front());
		queue.pop();
		for (int to(1); to <= lastDcc; ++to)
		{
			if (edge[v][to])
			{
				connect[to] |= connect[v];
				--in[to];
				if (in[to] == 0)
				{
					queue.push(to);
				}
			}
		}
	}

	int ans(0);
	for (int v(1); v <= lastDcc; ++v)
	{
		//printf("%d: ", v);
		for (int to(1); to <= lastDcc; ++to)
		{
			//printf("%d", int(connect[v][to]));
			if (connect[v][to])
			{
				ans += size[v] * size[to];
			}
		}
		//printf("\n");
	}
	io.write(ans, '\n');
	return 0;
}
