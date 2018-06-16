#include<bits/stdc++.h>
#define LL long long
#define MOD 1000000007
#define MAXN 100005
#define Pii pair<int,pair<int,int>>
#define P pair<int,int>
using namespace std;
int nd[2050][13];		//day number of each month in each year
bool leapjudge(int y){		//judge whether leap year
    if(y%4==0 && (y%100!=0 || y%400==0))return 1;
    else return 0;
}
int main(){
    for(int y=1900;y<2020;y++)
    for(int m=1;m<=12;m++){
        if(m==1) nd[y][m]=31;
        else if(m==2){
            if(leapjudge(y))nd[y][m]=29;
            else nd[y][m]=28;
        }
        else if(m==3) nd[y][m]=31;
        else if(m==4) nd[y][m]=30;
        else if(m==5) nd[y][m]=31;
        else if(m==6) nd[y][m]=30;
        else if(m==7) nd[y][m]=31;
        else if(m==8) nd[y][m]=31;
        else if(m==9) nd[y][m]=30;
        else if(m==10) nd[y][m]=31;
        else if(m==11) nd[y][m]=30;
        else if(m==12) nd[y][m]=31;
    }
    int ans=0;
    int now=0;
    int y=1900,m=1,d=1;
    while(y<=2001){
        now++; d++;
        if(d>nd[y][m]){
            m++;
            d=1;
        }
        if(m>12){
            y++;
            m=1;
        }
        now%=7;
        if(y>1900 && y<2001 && d==1 && now==6){
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
