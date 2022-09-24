#include<bits/stdc++.h>
using namespace std;
#define file(a) freopen(#a".in","r",stdin),freopen(#a".out","w",stdout)
#define LL long long
#define N 200010
struct llt{
	int val,lc,rc;
	int fa,d;
}t[N];
#define fa(x) t[x].fa
#define lc(x) t[x].lc
#define rc(x) t[x].rc
int find(int x){
	return x==fa(x)?x:fa(x)=find(fa(x));
}
inline void Swap(int &x,int &y){
	int tmp=x;x=y;y=tmp;
}
int merge(int x,int y){
	if(!x||!y) return x|y;
	if(t[x].val>t[y].val||(t[x].val==t[y].val&&x>y)) Swap(x,y);
	rc(x)=merge(rc(x),y);
	if(t[rc(x)].d>t[lc(x)].d) Swap(lc(x),rc(x));
	fa(x)=fa(lc(x))=fa(rc(x))=x;
	t[x].d=t[rc(x)].d+1;
	return x;
}
void pop(int x){
	t[x].val=-1;
	fa(rc(x))=rc(x);fa(lc(x))=lc(x);
	t[x].fa=merge(lc(x),rc(x));
}
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	t[0].d=-1;
	for(int i=1;i<=n;++i){
		int x;scanf("%d",&x);
		t[i].val=x;t[i].fa=i;
	}
	while(m--){
		int opt;
		scanf("%d",&opt);
		if(opt==1){
			int x,y;
			scanf("%d%d",&x,&y);
			int xx=find(x),yy=find(y);
			if(t[x].val==-1||t[y].val==-1) continue;
			if(xx==yy) continue;
			merge(xx,yy);
		}
		if(opt==2){
			int x;scanf("%d",&x);
			int xx=find(x);
			if(t[x].val==-1) printf("%d\n",-1);
			else{
				printf("%d\n",t[xx].val);
				pop(xx);
			}
		}
	}
	return 0;
}
