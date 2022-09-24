num = cnt;
for (int i = 1; i <= n; ++i)
	if (cut[i]) new_id[i] = ++num;

tc = 1;
for (int i = 1; i <= cnt; ++i)
{
	for (int j = 0; j < dcc[i].size(); ++j)
	{
		int x = dcc[i][j];
		if (cut[x])
		{
			add_c(i, new_id[x]);
			add_c(new_id[x], i);
		}
		else c[x] = i;
	}
}

printf("Vertices %d, Edges %d\n", num, tc / 2);
for (int i = 2; i < tc; i += 2)
	printf("%d %d\n", vc[i ^ 1], vc[i]);
