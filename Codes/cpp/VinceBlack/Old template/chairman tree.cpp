#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#define LL long long
#define MAXN 100050
#define INF 0x3f3f3f3f
#define rec(i,x) for(int i=0;i<x;i++)
#define rec1(i,x) for(int i=1;i<=x;i++)
#define rd(x) scanf("%d",&x)
using namespace std;

int n,m;
int tot;
int hsh[MAXN],blk[MAXN];
int tr[MAXN];
int lch[MAXN*20],rch[MAXN*20],sum[MAXN*20];
int build(int l,int r){
	int root=tot+1;
	tot++;
	sum[root]=0;
	if (l==r) return root;
	int mid=(l+r)/2;
	lch[root]=build(l,mid);
	rch[root]=build(mid+1,r);
	return root;
}
int update(int pre,int x,int l,int r){
	int root=tot+1;
	tot++;
	lch[root]=lch[pre];
	rch[root]=rch[pre];
	sum[root]=sum[pre]+1;

	if (l==r) return root;

	int mid=(l+r)/2;
	if (x<=mid) lch[root]=update(lch[pre],x,l,mid);
	else rch[root]=update(rch[pre],x,mid+1,r);
	return root;
}

int query(int x,int y,int k,int l,int r){
	if (l>=1 && r<=k){
		return sum[y]-sum[x];
	}
	int mid=(l+r)/2;
	int ans=query(lch[x],lch[y],k,l,mid);
	if (k>mid){
		ans+=query(rch[x],rch[y],k,mid+1,r);
	}
	return ans;
}

int main(){
	int t;
	int cnt=1;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++){
			scanf("%d",&blk[i]);
			hsh[i]=blk[i];
		}
		tot=0;
		sort(hsh+1,hsh+1+n);
		int zb=unique(hsh+1,hsh+1+n)-(hsh+1);
		tr[0]=build(1,zb);
		for (int i=1;i<=n;i++){
			int xx=lower_bound(hsh+1,hsh+zb+1,blk[i])-hsh;
			tr[i]=update(tr[i-1],xx,1,zb);
		}
		printf("Case %d:\n",cnt++);
		for(int i=1;i<=m;i++){
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			int lgs=lower_bound(hsh+1,hsh+zb+1,k)-hsh;
			l++;r++;
			if (hsh[lgs]>k){
				lgs--;
			}

			if (lgs>0){
				printf("%d\n",query(tr[l-1],tr[r],lgs,1,zb));
			}
			else{
				printf("0\n");
			}
		}
	}
	return 0;
}
