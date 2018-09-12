#include<bits/stdc++.h>
#define MAXN 10005
#define P pair<int,int>
using namespace std;

bool isopr[MAXN];
int op[MAXN];
char s[MAXN];
stack<int> optr;
stack<P>    opnd;
int p;
void gao2(){
	P ans;
	P b = opnd.top(); opnd.pop();
	P a = opnd.top(); opnd.pop();
	int t=optr.top(); optr.pop();
	if(t=='+'){
		ans=P(a.first+b.first,a.second+b.second);
	}
	else if(t=='-'){
		ans=P(a.first-b.second,a.second-b.first);
	}
	else if(t=='*'){
		int t1=a.first*b.first;
        int mn=t1,mx=t1;
		int t2=a.first*b.second;
		mn=min(mn,t2),mx=max(mx,t2);
		int t3=a.second*b.first;
		mn=min(mn,t3),mx=max(mx,t3);
		int t4=a.second*b.second;
		mn=min(mn,t4),mx=max(mx,t4);
		ans=P(mn,mx);
	}
	else if(t=='d'){
		ans=P(a.first,a.second*b.second);
	}
	opnd.push(ans);
}
char C_M_P[8][8]={
//   +   -   *    d   (   )   %
	{'>','>','<','<','<','>','>'}, //+
	{'>','>','<','<','<','>','>'}, //-
	{'>','>','>','<','<','>','>'}, //*
	{'>','>','>','>','<','>','>'}, //d
	{'<','<','<','<','<','=','0'}, //(
	{'>','>','>','>','0','>','>'}, //)
	{'<','<','<','<','<','0','='}  //%
};
int optrToi[200];
char cmp(int a,int b){
	return C_M_P[optrToi[a]][optrToi[b]];
}
void gao(){
	optr.push('%');
	for(int i=0;i<p;i++){
		if(isopr[i]){
			if(op[i]=='%'){
				if(optr.size()>0){
					int tmp=optr.top();
					while(tmp!='%'){
						gao2();
						tmp=optr.top();
					}
				}
				return;
			}
			int tmp=optr.top();
			char relation=cmp(tmp,op[i]);
			if(relation=='>'){
				gao2();
				--i;
			}
			else if(relation=='<'){
				optr.push(op[i]);
			}
			else{
				optr.pop();
			}
		}
		else{
			opnd.push(P(op[i],op[i]));
		}
	}
}


int main(){
	optrToi['+']=0;
	optrToi['-']=1;
	optrToi['*']=2;
	optrToi['d']=3;
	optrToi['(']=4;
	optrToi[')']=5;
	optrToi['%']=6;
	while(scanf("%s",s)!=EOF){
		memset(isopr,0,sizeof(isopr));
		memset(op,0,sizeof(op));
		while(!optr.empty())optr.pop();
        while(!opnd.empty())opnd.pop();
		int len=strlen(s);
		p=0;
		for(int i=0;i<len;i++){
			if(!isdigit(s[i])){
				isopr[p]=1;
				op[p++]=(int)s[i];
			}
			else{
				int j=i;
				op[p]=s[i]-'0';
				while(j<len-1&&(isdigit(s[j+1]))){
					j++;
					op[p]=op[p]*10+s[j]-'0';
					i=j;
				}
				p++;
			}
		}
		isopr[p]=1;
		op[p++]=(int)'%';
		gao();
		printf("%d %d\n",opnd.top().first,opnd.top().second);
	}

	return 0;
}
