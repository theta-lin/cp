// https://zhuanlan.zhihu.com/p/115243708

const int MAXN = 30005, MAXQ = 200005, MAXM = 1000005;
int sq;
struct query
{
    int l, r, id;
    bool operator<(const query &o) const
    {
        if (l / sq != o.l / sq)
            return l < o.l;
        if (l / sq & 1)
            return r < o.r;
        return r > o.r;
    }
} Q[MAXQ];
int A[MAXN], ans[MAXQ], Cnt[MAXM], cur, l = 1, r = 0;
inline void add(int p)
{
    if (Cnt[A[p]] == 0)
        cur++;
    Cnt[A[p]]++;
}
inline void del(int p)
{
    Cnt[A[p]]--;
    if (Cnt[A[p]] == 0)
        cur--;
}
int main()
{
    int n = read();
    sq = sqrt(n);
    for (int i = 1; i <= n; ++i)
        A[i] = read();
    int q = read();
    for (int i = 0; i < q; ++i)
        Q[i].l = read(), Q[i].r = read(), Q[i].id = i;
    sort(Q, Q + q);
    for (int i = 0; i < q; ++i)
    {
        while (l > Q[i].l)
            add(--l);
        while (r < Q[i].r)
            add(++r);
        while (l < Q[i].l)
            del(l++);
        while (r > Q[i].r)
            del(r--);
        ans[Q[i].id] = cur;
    }
    for (int i = 0; i < q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
