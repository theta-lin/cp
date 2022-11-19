// https://blog.csdn.net/weixin_46870692/article/details/124654674

#include<stdio.h>
#include<math.h>
#include<algorithm>

using namespace std;
const int N = 1e6 + 10;
struct node{
	int l,r;
	int time,id;
}pen[4 * N];
struct Color{
	int p,c;
	int time;
}color[N];
int pos[N],a[N],res[N],cnt[N];
int n,m;

bool cmp(node a1,node a2) {
	if(pos[a1.l] != pos[a2.l]) return pos[a1.l] < pos[a2.l];
	else if(pos[a1.r] != pos[a2.r]) return pos[a1.r] < pos[a2.r];
	else return a1.time < a2.time;
}

void work() {
	int l = 0, r = 0,now = 0,time = 0;

	for(int i=1;i<=m;i++) {
		int ql = pen[i].l;
		int qr = pen[i].r;
		int qt = pen[i].time;

		while(l < ql) {
			cnt[a[l]] --;
			if(cnt[a[l]] == 0) now --;
			l ++;
		}

		while(l > ql) {
			l --;
			cnt[a[l]] ++;
			if(cnt[a[l]] == 1) now ++;
		}

		while(r < qr) {
			r ++;
			cnt[a[r]] ++;
			if(cnt[a[r]] == 1) now ++;
		}

		while(r > qr) {
			cnt[a[r]] --;
			if(cnt[a[r]] == 0) now --;
			r --;
		}

		while(time < qt) {
			time ++;
			int p = color[time].p;
			int c = color[time].c;
			if(p >= l && p <= r) {
				cnt[a[p]] --;
				if(cnt[a[p]] == 0) now --;

				cnt[c] ++;
				if(cnt[c] == 1) now ++;

			}

			swap(a[p],color[time].c);
		}

		while(time > qt) {
			int p = color[time].p;
			int c = color[time].c;
			if(p >= l && p <= r) {
				cnt[a[p]] --;
				if(cnt[a[p]] == 0) now --;

				cnt[c] ++;
				if(cnt[c] == 1) now ++;
			}

			swap(a[p],color[time].c);
			time --;
		}

		res[pen[i].id] = now;
	}
}

int main(){
	scanf("%d %d",&n,&m);

	int t = pow(n,2.0/3.0);

	int size = ceil((double)n / t);

	for(int i=1;i<=size;i++) {
		for(int j=(i-1)*t+1;j<=min(i*t,n);j++) {
			pos[j] = i;
		}
	}

	for(int i=1;i<=n;i++) scanf("%d",&a[i]);

	int L = 0,k = 0;

	for(int i=1;i<=m;i++) {
		char s[2] = {0};
		scanf("%s",s);

		if(s[0] == 'Q') {
			k ++;
			scanf("%d %d",&pen[k].l,&pen[k].r);
			pen[k].time = L;
			pen[k].id = k;
		}
		else {
			L ++;
			scanf("%d %d",&color[L].p,&color[L].c);
			color[L].time = L;
		}
	}

	sort(pen+1,pen+1+k,cmp);
	m = k;

	work();

	for(int i=1;i<=m;i++) printf("%d\n",res[i]);

	return 0;
}
