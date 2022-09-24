int hc[SIZE], vc[SIZE * 2], nc[SIZE * 2], tc;
void add_c(int x, int y)
{
	vc[++tc] = y, nc[tc] = hc[x], hc[x] = tc;
}

tc = 1;
for (int i = 2; i <= tot; ++i)
{
	int x = ver[i ^ 1], y = ver[i];
	if (c[x] == c[y]) continue;
	add_c(c[x], c[y]);
}

printf("Vertices %d, Edges %d\n", dcc, tc / 2);
for (int i = 2; i < tc; ++i)
	printf("%d %d\n", vc[i ^ 1], vc[i]);
