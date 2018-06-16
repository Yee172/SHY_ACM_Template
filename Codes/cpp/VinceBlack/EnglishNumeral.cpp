#include<bits/stdc++.h>
#define LL long long
#define MOD 1000000007
#define MAXN 100005
#define Pii pair<int,pair<int,int>>
#define P pair<int,int>
using namespace std;
string num[1005]={
"zero",
"one",
"two",
"three",
"four",
"five",
"six",
"seven",
"eight",
"nine",
"ten",
"eleven",
"twelve",
"thirteen",
"fourteen",
"fifteen",
"sixteen",
"seventeen",
"eighteen",
"nineteen",
"twenty"
};

int main(){
    num[30]="thirty";
    num[40]="forty";
    num[50]="fifty";
    num[60]="sixty";
    num[70]="seventy";
    num[80]="eighty";
    num[90]="ninety";
    num[1000]="onethousand";
    for(int i=2;i<=9;i++)
    for(int j=1;j<=9;j++){
        num[i*10+j]=num[i*10]+num[j];
    }
    for(int i=100;i<=900;i+=100){
        num[i]=num[i/100] + "hundred";
    }
    for(int i=101;i<=999;i++)if(i%100!=0){
        num[i]=num[i/100*100]+"and"+num[i%100];
    }
    int ans=0;
    for(int i=1;i<=1000;i++) ans+=num[i].length();
    cout<<ans;
    return 0;
}
