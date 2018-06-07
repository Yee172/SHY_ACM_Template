//���ಢ�鼯
int f[MAXN],group[MAXN];
int getf(int x){
   if (f[x]==x) return x;
   int fa=getf(f[x]);
   //���嵱ǰ�ڵ�����Ƚڵ�Ĺ�ϵ //change according to the task
   return f[x]=fa;
}
bool union_set(int type,int x,int y){
   int fx=find(x);
   int fy=find(y);
   if (fx==fy){
       //x,y�ĸ�����ͬ�����۳���ʽ�ж����Ƿ����
   }
   else{
       //x,y���ײ�ͬ������֮�⻹Ҫ�ϲ�
	   //ע�����������ʹ��getf����Ϊgetf���Զ�����ڵ�����ȵĹ�ϵ�����ܻ���ɻ��ҡ�
       f[fx]=fy;
       return;
   }
}

//���ӣ�ʳ���� POJ - 1182
/* 
���������������ද��A,B,C�������ද���ʳ������������Ȥ�Ļ��Ρ�A��B�� B��C��C��A�� 
����N�������1��N��š�ÿ�����ﶼ��A,B,C�е�һ�֣��������ǲ���֪������������һ�֡�
����������˵������N�����������ɵ�ʳ������ϵ���������� 
��һ��˵����"1 X Y"����ʾX��Y��ͬ�ࡣ 
�ڶ���˵����"2 X Y"����ʾX��Y�� 
���˶�N���������������˵����һ���һ���˵��K�仰����K�仰�е�����ģ��е��Ǽٵġ���һ�仰������������֮һʱ����仰���Ǽٻ�����������滰�� 
1�� ��ǰ�Ļ���ǰ���ĳЩ��Ļ���ͻ�����Ǽٻ��� 
2�� ��ǰ�Ļ���X��Y��N�󣬾��Ǽٻ��� 
3�� ��ǰ�Ļ���ʾX��X�����Ǽٻ��� 
��������Ǹ��ݸ�����N��1 <= N <= 50,000����K�仰��0 <= K <= 100,000��������ٻ��������� 
Input
��һ������������N��K����һ���ո�ָ��� 
����K��ÿ�������������� D��X��Y������֮����һ���ո����������D��ʾ˵�������ࡣ 
��D=1�����ʾX��Y��ͬ�ࡣ 
��D=2�����ʾX��Y��
Output
ֻ��һ����������ʾ�ٻ�����Ŀ��
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
