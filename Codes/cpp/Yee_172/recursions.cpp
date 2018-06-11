#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 200050

// Joseph problem:
// n people stand in a circle labeled from 0,
// at the beginning, people labeled 0 counts 1,
// then the next people counts the last counted number plus 1,
// each kill happens until someone counts the exact number m,
// then the people next the dead people counts from 1,
// this process ends when only one person stands on the ground.
ll get_joseph(ll n, ll m) // return who stands to the last labeled from 0
{
    if (n == 1) return 0;
    else return (get_joseph(n - 1, m) + m) % n;
}
