#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<queue>
#include<map>
#define MAXN
#define MAXP
#define rec(i,x) for(int i=0;i<x;i++)
#define REC(i,x) for(int i=1;i<=x;i++)
#define rd(i) scanf("%d",&i);
using namespace std;

int A[MAXN],n,N;//n:original num, N:extanded number
int Sum[MAXN<<2];//sum of interval
int Add[MAXN<<2];//lazy note

void build(int n){ //build a segment tree with node from 1..n
	N=1;
	while(N<n+2) N<<=1;
	for (int i=1;i<=n;i++) Sum[N+i]=A[i];
	for (int i=N-1;i>0;i--){
		Sum[i]=Sum[i<<1]+Sum[i<<1|1];
		Add[i]=0;
	}
}
//
//void Update(int L,int C){ //A[L]+=C;
//	for (int s=N+L;s;s>>=1){
//		Sum[s]+=C;
//	}
//}
//int Query(int L,int R) //find sum[L,R]
//{
//	int ANS=0;
//	for (int s=N+L-1,t=N+R+1;s^t^1;s>>=1,t>>=1){
//		if (~s&1) ANS+=Sum[s^1];
//		if ( t&1) ANS+=Sum[t^1];
//
//	}
//	return ANS;
//}
void Update(int L,int R,int C) //A[L..R]+=C
{
	int s,t,Ln=0,Rn=0,x=1; //Ln and Rn means the number of nodes that the left final node and right final node has
	for (s=N+L-1,t=N+R+1;s^t^1;s>>=1,t>>=1,x<<=1){ //x means the number of sons that each node in this level has
		Sum[s]+=C*Ln;
		Sum[t]+=C*Rn;
		if (~s&1) Add[s^1]+=C,Sum[s^1]+=C*x,Ln+=x;
		if ( t&1) Add[t^1]+=C,Sum[t^1]+=C*x,Rn+=x;
	}
	for (;s;s>>=1,t>>=1){
		Sum[s]+=C*Ln;
		Sum[t]+=C*Rn;
	}
}
int Query(int L,int R){ //find Sum[L..R]
	int s,t,Ln=0,Rn=0,x=1;
	int ANS=0;
	for(s=N+L-1,t=N+R+1;s^t^1;s>>=1,t>>=1,x<<=1){
		if (Add[s]) ANS+=Add[s]*Ln;
		if (Add[t]) ANS+=Add[t]*Rn;
		if (~s&1) ANS+=Sum[s^1],Ln+=x;
		if ( t&1) ANS+=Sum[t^1],Rn+=x;
	}

	for (;s;s>>=1,t>>=1){
		ANS+=Add[s]*Ln;
		ANS+=Add[t]*Rn;
	}
	return ANS;
}
