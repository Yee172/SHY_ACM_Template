#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 200050
#define TYPE ll


// ---------------------------------------------------------------------------------------------------------------------
// Joseph problem:
// n people stand in a circle labeled from 0,
// at the beginning, people labeled 0 counts 1,
// then the next people counts the last counted number plus 1,
// each kill happens until someone counts the exact number m,
// then the people next the dead people counts from 1,
// this process ends when only one person stands on the ground.
TYPE get_joseph(TYPE n, TYPE m)
{
    if (n == 1) return 0;
    else return (get_joseph(n - 1, m) + m) % n;
}
// return who stands to the last labeled from 0

TYPE a[MAXN];
void init_joseph(TYPE m)
{
    a[0] = a[1] = 0;
    for (ll i = 2; i < MAXN; i++) a[i] = (a[i - 1] + m) % i;
}
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// A008904 - OEIS
// a[n] = final nonzero digit of n!
TYPE a[MAXN];
TYPE ini[] = {1, 1, 2, 6, 4, 4, 4, 8, 4, 6};
void initialize()
{
    a[0] = a[1] = 1;
    for (ll i = 2; i < MAXN; i++)
    {
        a[i] = 1;
        for (ll j = 0; j < i / 5 % 4; j++) a[i] *= 3;
        a[i] *= 6 * ini[i % 10] * a[i / 5];
        a[i] %= 10;
    }
}
// ---------------------------------------------------------------------------------------------------------------------
