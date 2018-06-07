//种类并查集
int f[MAXN],group[MAXN];
int getf(int x){
   if (f[x]==x) return x;
   int fa=getf(f[x]);
   //理清当前节点和祖先节点的关系 //change according to the task
   return f[x]=fa;
}
bool union_set(int type,int x,int y){
   int fx=find(x);
   int fy=find(y);
   if (fx==fy){
       //x,y的父亲相同，讨论出公式判断这是否合理
   }
   else{
       //x,y父亲不同，讨论之外还要合并
	   //注意在这里谨慎使用getf，因为getf会自动处理节点和祖先的关系，可能会造成混乱。
       f[fx]=fy;
       return;
   }
}

//例子：食物链 POJ - 1182
/* 
动物王国中有三类动物A,B,C，这三类动物的食物链构成了有趣的环形。A吃B， B吃C，C吃A。 
现有N个动物，以1－N编号。每个动物都是A,B,C中的一种，但是我们并不知道它到底是哪一种。
有人用两种说法对这N个动物所构成的食物链关系进行描述： 
第一种说法是"1 X Y"，表示X和Y是同类。 
第二种说法是"2 X Y"，表示X吃Y。 
此人对N个动物，用上述两种说法，一句接一句地说出K句话，这K句话有的是真的，有的是假的。当一句话满足下列三条之一时，这句话就是假话，否则就是真话。 
1） 当前的话与前面的某些真的话冲突，就是假话； 
2） 当前的话中X或Y比N大，就是假话； 
3） 当前的话表示X吃X，就是假话。 
你的任务是根据给定的N（1 <= N <= 50,000）和K句话（0 <= K <= 100,000），输出假话的总数。 
Input
第一行是两个整数N和K，以一个空格分隔。 
以下K行每行是三个正整数 D，X，Y，两数之间用一个空格隔开，其中D表示说法的种类。 
若D=1，则表示X和Y是同类。 
若D=2，则表示X吃Y。
Output
只有一个整数，表示假话的数目。
Sample Input
100 7
1 101 1 
2 1 2
2 2 3 
2 3 3 
1 1 3 
2 3 1 
1 5 5
Sample Output
3 */
#include<cstdio>
#define MAXN 100005
#define INF 0x3f3f3f3f
#define LL long long
#define P pair<double,int>
using namespace std;
int f[MAXN],C[MAXN];
int getf(int x){
    if(x==f[x]) return x;
    int fx=getf(f[x]);
    C[x]=(C[x]+C[f[x]])%3;
    return f[x]=fx;
}
int mergef(int x,int y,int r){
    int fx=getf(x);
    int fy=getf(y);
    if(fx==fy){
        if((r+C[y])%3!=C[x]){
            return 0;
        }
    }
    else{
        C[fx]=((r+C[y])-C[x]+3)%3;
        f[fx]=fy;
    }
    return 1;
}
int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) f[i]=i, C[i]=0;
    int ans=0;
    for(int i=1;i<=q;i++){
        int D,x,y;
        scanf("%d%d%d",&D,&x,&y);
        if(x>n||y>n) ans++;
        else if(!mergef(x,y,D-1)) ans++;
    }
    printf("%d",ans);
    return 0;
}
