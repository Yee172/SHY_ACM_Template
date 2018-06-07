#include<bits/stdc++.h>
#define rec(i,x) for(int i=0;i<x;i++)
#define MAXN 200005
#define INF 0x3f3f3f3f
#define LL long long
#define ll long long
#define P pair<double,int>
using namespace std;

template<typename TI>
struct BitOp{
    //返回：反转pos开始，往右长度为len的区域
	inline TI flip(TI op,size_t pos,size_t len=1){return op^(((1<<len)-1)<<pos);}
	//修改op：将pos开始，长度为len区域的值，设成v的二进制表示形式
	inline TI& set(TI& op,size_t pos,int v,size_t len=1){
		int o = ((1<<len)-1);
		return op = (op&(~(o<<pos)))|((v&o)<<pos);
	}
	//返回：从pos开始，长度为len的区域
	inline int get(TI op,size_t pos, size_t len=1){return (op>>pos)&((1<<len)-1);}
	//输出二进制，例子：bo.outBits(cout,5);
	ostream& outBits(ostream& os, TI i){
		if(i)outBits(os,(i>>1))<<(i&1);
		return os;
	}
};
BitOp<int> bo;
int main(){
    int a=1;
    bo.outBits(cout,5);
    return 0;
}
