#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 200050
#define TYPE ll
#define mod 0x3b9aca07


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
    for (ll i = 2; i < MAXN; i++)
        a[i] = (a[i - 1] + m) % i;
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


// ---------------------------------------------------------------------------------------------------------------------
// A011900 - OEIS
// Related to A046090
// Solution to b * (b - 1) = 2 * a * (a - 1) in natural numbers
// a[n] = the n-th of a in ascending order
TYPE a[MAXN];
void initialize()
{
    a[0] = 1, a[1] = 3;
#ifdef mod
    for (ll i = 2; i < MAXN; i++)
        a[i] = (6 * a[i - 1] % mod - a[i - 2] - 2 + 2 * mod) % mod;
#else
    for (ll i = 2; i < MAXN, i <= 25; i++)
        a[i] = 6 * a[i - 1] - a[i - 2] - 2;
    // MAXIMUM 25 for long long
#endif
}
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// A046090 - OEIS
// Related to A011900
// Solution to a * (a - 1) = 2 * b * (b - 1) in natural numbers
// a[n] = the n-th of a in ascending order
TYPE a[MAXN];
void initialize()
{
    a[0] = 1, a[1] = 4;
#ifdef mod
    for (ll i = 2; i < MAXN; i++)
        a[i] = (6 * a[i - 1] % mod - a[i - 2] - 2 + 2 * mod) % mod;
#else
    for (ll i = 2; i < MAXN, i <= 25; i++)
        a[i] = 6 * a[i - 1] - a[i - 2] - 2;
    // MAXIMUM 25 for long long
#endif
}
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// A166079 - OEIS
// Related to A185456
// Given a row of n pay phones, all initially unused,
// a[n] people can use the pay phones, assuming
// (1) each always chooses one of the most distant
//     pay phones from those in use already,
// (2) the first person takes a phone at the end,
// (3) no people use adjacent phones.
TYPE a[MAXN];
void initialize()
{
    a[0] = 0, a[1] = a[2] = 1, a[3] = 2;
    for (ll i = 4; i < MAXN; i++)
        a[i] = a[i + 1 >> 1] + a[i + 2 >> 1] - 1;
}
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// A185456 - OEIS
// Related to A166079
// Assume that the first person to use a bank of pay phones
// selects one at the end, and all subsequent users select the
// phone which puts them furthest from the current phone users.
// a[n] is the smallest number of phones such that n may be
// used without any two adjacent phones being used.
// For example:
//     n = 4
//     one possible solution is P..P.P.P
//  => need 8 pay phones
TYPE a[MAXN];
void initialize()
{
    a[0] = 0, a[1] = 1, a[2] = 3;
    for (ll i = 1; i + 2 < MAXN; i <<= 1)
    {
        a[i + 2] = a[i + 1] + i + 1;
        for (ll j = 1; j < i, j + i + 2 < MAXN; j++)
            a[j + i + 2] = a[j + i + 1] + 1;
    }
}
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// Double direction truncatable primes
// PE - Problem 37
// Take 3797 for example:
//     3797, 797, 97, 7 & 3797, 379, 37, 3 are all primes
// Only eleven primes that are double direction truncatable
TYPE a[] = {23, 37, 53, 73, 313, 317, 373, 797, 3137, 3797, 739397};
// ---------------------------------------------------------------------------------------------------------------------
