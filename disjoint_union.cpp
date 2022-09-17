int find(int v)
{
	if (belong[v] == v)
	{
		return v;
	}
	else
	{
		return belong[v] = find(belong[v]);
	}
}
