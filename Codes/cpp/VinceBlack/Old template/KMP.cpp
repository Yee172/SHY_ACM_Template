#include<bits/stdc++.h>
#define MAXN 75
using namespace std;
string s;
string pattern[155];
int nxt[MAXN];
void getnxt(string& p){
    int sz=p.length();
    nxt[0]=0;
    for(int i=1,j=0;i<sz;i++){
        while(j>0 && p[i]!=p[j]) j=nxt[j-1];
        if(p[i]==p[j])++j;
        nxt[i]=j;
    }
}
int KMP(string& p){
    int m=p.length();
    int sz=s.length();
    int cnt=0;
    for(int i=0,j=0;i<sz;i++){
        while((j>=m)||(j>0 && s[i]!=p[j])) j=nxt[j-1];
        if(s[i]==p[j]) ++j;
        if(j==m) ++cnt;
    }
    return cnt;
}

int main(){
    ios::sync_with_stdio(false);
    int n;
    while(cin>>n){
        if(n==0) break;
        vector<string> ans;
        for(int i=0;i<n;i++) cin>>pattern[i];
        cin>>s;
        int mx=-1;
        for(int i=0;i<n;i++){
            getnxt(pattern[i]);
            int res=KMP(pattern[i]);
            if(res>mx){
                mx=res;
                ans.clear();
                ans.push_back(pattern[i]);
            }
            else if(res==mx)ans.push_back(pattern[i]);
        }
        cout<<mx<<endl;
        int sz=ans.size();
        for(int i=0;i<sz;i++) cout<<ans[i]<<endl;
    }

    return 0;
}

