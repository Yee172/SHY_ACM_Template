//#include<cstdio>
//#include<cstring>
//#include<vector>
//#include<queue>
//#include<algorithm>
//#include<cmath>
//#define LL long long
//#define MAXN 100050
//#define INF 0x3f3f3f3f
//#define rec(i,x) for(int i=0;i<x;i++)
//#define rec1(i,x) for(int i=1;i<=x;i++)
//#define rd(x) scanf("%d",&x)
//using namespace std;
//int f[MAXN],group[MAXN];
//
//int getf(int x){
//    if (f[x]==x) return x;
//    int fa=getf(f[x]);
//    group[x]=(group[x]+group[f[x]])%3; //change according to the task
//    return f[x]=fa;
//}
//
//bool union_set(int type,int x,int y){
//    int fx=find(x);
//    int fy=find(y);
//    if (fx==fy){
//        //x,y�ĸ�����ͬ�����۳���ʽ�ж����Ƿ����
//    }
//    else{
//        //x,y���ײ�ͬ������֮�⻹Ҫ�ϲ�
//        f[fx]=fy;
//        return;
//    }
//
//}
//����Ϊ���ಢ�鼯
//
int getf(int x){
    if (f[x]==x) return x;
    int fa=getf(f[x]);
    return f[x]=fa;
}
int getf(int x){//�ǵݹ�
    int k,j,r;
    r=x;
    while(r!=f[r]) r=f[r];
    k=x;
    while(k!=r){
        j=f[k];
        f[k]=r;
        k=j;
    }
    return r;
}
bool mergef(int x,int y){
    int fx=getf(x),fy=getf(y);
    if (fx!=fy){
        f[fx]=fy;
        return true;
    }
    else {
        return false;
    }
}
