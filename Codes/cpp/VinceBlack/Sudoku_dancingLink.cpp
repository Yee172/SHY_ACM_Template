#include<bits/stdc++.h>
#define P pair<int,pair<int,int> >
#define MAXNODE 300010
#define MAXM 1010
#define MAXN 1010
using namespace std;
struct DancingLink{
    int n,m,sz;
    int U[MAXNODE],D[MAXNODE],L[MAXNODE],R[MAXNODE],Row[MAXNODE],Col[MAXNODE];
    int H[MAXN],S[MAXM];
    int ansd,ans[MAXN];
    void init(int _n,int _m)
    {
        n=_n,m=_m;
        for(int i=0; i<=m; i++){
            S[i]=0;
            U[i]=D[i]=i;
            L[i]=i-1,R[i]=i+1;
        }
        R[m]=0,L[0]=m;
        sz=m;
        for(int i=1; i<=n; i++) H[i]=-1;
    }
    void AddNode(int r,int c)
    {
        ++S[Col[++sz]=c];
        Row[sz]=r;
        D[sz]=D[c];
        U[D[c]]=sz;
        U[sz]=c;
        D[c]=sz;
        if(H[r]<0){
            H[r]=L[sz]=R[sz]=sz;
        }else{
            R[sz]=R[H[r]];
            L[R[H[r]]]=sz;
            L[sz]=H[r];
            R[H[r]]=sz;
        }
    }
    void RowDelete(int c)
    {
        L[R[c]]=L[c];R[L[c]]=R[c];
        for(int i=D[c]; i!=c; i=D[i])
        for(int j=R[i]; j!=i; j=R[j]){
            U[D[j]]=U[j];
            D[U[j]]=D[j];
            --S[Col[j]];
        }
    }
    void RowResume(int c)
    {
        for(int i=U[c]; i!=c; i=U[i])
        for(int j=L[i]; j!=i; j=L[j]){
            U[D[j]]=D[U[j]]=j;
            ++S[Col[j]];
        }
        L[R[c]]=R[L[c]]=c;
    }
    bool dance(int d)
    {
        if(R[0]==0){
            ansd=d;
            return true;
        }
        int c=R[0];
        for(int i=R[0]; i!=0; i=R[i]){
            if(S[i]<S[c])
                c=i;
        }
        RowDelete(c);
        for(int i=D[c]; i!=c; i=D[i]){
            ans[d]=Row[i];
            for(int j=R[i]; j!=i; j=R[j]) RowDelete(Col[j]);
            if(dance(d+1)) return true;
            for(int j=L[i]; j!=i; j=L[j]) RowResume(Col[j]);
        }
        RowResume(c);
        return false;
    }
}dlx;
int getblock(int r,int c,int x){
	if(r<4&&c<4)return x;
	if(r<4&&c<7)return 9+x;
	if(r<4)return 18+x;

	if(r<7&&c<4)return 27+x;
	if(r<7&&c<7)return 36+x;
	if(r<7)return 45+x;

	if(r<10&&c<4)return 54+x;
	if(r<10&&c<7)return 63+x;
	else return 72+x;
}
int getrow(int r,int c,int x){
	return 81+9*(r-1)+x;
}
int getcol(int r,int c,int x){
	return 162+9*(c-1)+x;
}
int getCor(int r,int c){
    return 243+(r-1)*9+c;
}
int mx[15][15];
P colToCor[MAXM];
int main()
{

    while(1)
    {
        for(int i=1;i<=9;i++)
            for(int j=1;j<=9;j++)
            scanf("%d",&mx[i][j]);
        int n=0,m=324;
        for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            int tmp=mx[i][j];
            if(tmp!=0){
                n++;
            }
            else{
                n+=9;
            }
        }
        int tot=0;
        dlx.init(n,m);
        for(int i=1;i<=9;i++)
            for(int j=1;j<=9;j++)
            {
                int tmp;
                tmp = mx[i][j];
                if(tmp!=0){
                    dlx.AddNode(++tot,getblock(i,j,tmp));
                    dlx.AddNode(tot,getrow(i,j,tmp));
                    dlx.AddNode(tot,getcol(i,j,tmp));
                    dlx.AddNode(tot,getCor(i,j));
                    colToCor[tot]=P(tmp,pair<int,int>(i,j));
                }
                else{
                    for(int k=1;k<=9;k++){
                        dlx.AddNode(++tot,getblock(i,j,k));
                        dlx.AddNode(tot,getrow(i,j,k));
                        dlx.AddNode(tot,getcol(i,j,k));
                        dlx.AddNode(tot,getCor(i,j));
                        colToCor[tot]=P(k,pair<int,int>(i,j));
                    }
                }
            }
        memset(mx,0,sizeof(mx));
        if(!dlx.dance(0)) printf("NO\n");
        else{
            for(int i=0; i<dlx.ansd; i++){
                int cc = dlx.ans[i];
                int x = colToCor[cc].second.first;
                int y = colToCor[cc].second.second;
                int k = colToCor[cc].first;
                mx[x][y] = k;
            }
            for(int i=1;i<=9;i++)
            {
                for(int j=1;j<=9;j++)
                    printf("%d ",mx[i][j]);
                puts("");
            }
        }
    }
    return 0;
}
