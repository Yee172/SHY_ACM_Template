#include<bits/stdc++.h>
#define MAXN 1000005
#define MOD 20071027
#define LL long long
#define VinceBlack ios::sync_with_stdio(false);
using namespace std;
int p[MAXN<<1];
int manacher(char* s)//manacher模板 最大回文子串 数组要开MAXN*2
{
    memset(p,0,sizeof(p));
    int l=strlen(s);
    int cur=0;
    int ans=0;
    for(int i=l;i>=0;i--)
	{
		s[(i<<1)+2]=s[i];
		s[(i<<1)+1]='#';
	}
	s[0]='*';
    for(int i=2;i<(l<<1)+1;i++)
    {
        if(p[cur]+cur>=i) p[i]=min(p[(cur<<1)-i],p[cur]+cur-i);
        else p[i]=1;
        while(s[i-p[i]]==s[i+p[i]])p[i]++;
        if(p[cur]+cur-i-p[i]<0)cur=i;
        ans=max(ans,p[i]);
    }
    return ans-1;
}
char tmp[MAXN<<1];
int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%s",tmp);
        printf("%d\n",manacher(tmp));
    }
    return 0;
}
