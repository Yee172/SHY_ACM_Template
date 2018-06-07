#include<bits/stdc++.h>
#define MAXN 200005
#define INF 0x3f3f3f3f
#define LL long long
#define P pair<double,int>
using namespace std;
int main()
{
    printf("")
    return 0;
}
/*问题描述：
现在有 $N$ 个工作。每个工作i的开始时间是$IL_i$，结束时间是$IR_i$。一个人同时只能做一份工作，每份工作必须从开始时间开始做到结束时间。如果有两份工作，前一份的结束时间等于后一份的开始时间，是可以做完前一份工作之后立即做后一份的。

现在有$Q$个工作者，工作者k在[$QL_k$,$QR_k$]时间内有空。当$QL_k$<=$IL_i$,且$IR_i$<=$QR_k$时，工作者k可以去做工作i。每个人都想在自己有空的时间，做尽可能多的工作。多个人去做同一份工作也是允许的。

写一个程序，求出每个人能做的工作的最大数量。

输入：
 _N Q

IL1 IR1

…

ILN IRN

QL1 QR1

…

QLQ QRQ_

第一行输入两个整数N，Q，N是工作的数量，Q是工作者的数量。
对于接下来的N行，第i行有两个整数ILi，IRi，ILi是工作i的开始时间，IRi是工作i的结束时间。
对于接下来的Q行，第K行有两个整数QLi，QRi，工作者k在[QLk,QRk]时间内有空。

输出：
输出一共Q行，每行输出一个整数，第k行输出第k个工作者最多能做的工作数量。

数据范围：
1<=N,Q<=1e5
-1e9<=ILi<IRi<=1e9
-1e9<=QLi<QRi<=1e9

样例输入1：
5 4
0 20
30 40
20 30
10 25
25 40
10 30
0 40
20 40
0 30

样例输出1：
1
3
2
2*/
