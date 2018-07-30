#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 200050
#define TYPE ll
#define MOD 0x3b9aca07


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
// return who stands to the last labeled from 0.

TYPE a[MAXN];
void init_joseph(TYPE m)
{
    a[0] = a[1] = 0;
    for (ll i = 2; i < MAXN; i++)
        a[i] = (a[i - 1] + m) % i;
}
// ---------------------------------------------------------------------------------------------------------------------

// A000005
// A000041
// A000793
// A000201
// Wythoff pairs

// ---------------------------------------------------------------------------------------------------------------------
// A000267 - OEIS
// {1, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, ...}
// Integer part of square root of 4 * n + 1.
// [*] This sequence can simplify discussion of this form:
//         If (n + 1 = p * p),
//             a(n) = 2 * p - 1;
//         If (p * p < n + 1 <= p * (p + 1)),
//             a(n) = 2 * p;
//         If (p * (p + 1) < n + 1 < (p + 1) * (p + 1)),
//             a(n) = 2 * p + 1.
// a[n] = int(sqrt(4 * n + 1))
// I recommend other languages with high precision
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// A001462 - OEIS
// {N/A, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, ...}
// Golomb's sequence.
// a(1) = 1; a(n + 1) = 1 + a(n + 1 - a(a(n))).
// a[n] = the number of times n occurs.
TYPE a[MAXN];
void initialize()
{
    a[0] = 0; // N/A
    a[1] = 1;
    for (ll i = 2; i < MAXN; i++)
        a[i] = 1 + a[i - a[a[i - 1]]];
}

vector<TYPE> indices;
template <typename T>
TYPE find_index(T x)
{
    return (TYPE) (lower_bound(indices.begin(), indices.end(), (TYPE) x) - indices.begin());
}
void initialize()
{
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);
    TYPE x = 0;
    for (ll i = 3; x <= MAXN; i++)
    {
        x = *(indices.end() - 1) + find_index(i);
        indices.push_back(x);
    }
}
template <typename T>
TYPE get_a(T n)
{
    assert(n > 0);
    return find_index(n);
}
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// A006522 - OEIS
// {1, 0, 0, 1, 4, 11, 25, 50, 91, 154, 246, 375, 550, ...}
// Number of regions created by sides and diagonals of n-gon in general position.
// Also is the 4-dimensional analog of centered polygonal numbers.
// a(n) = binomial(n, 4) + binomial(n - 1, 2)
//      = (n ^ 4 - 6 * n ^ 3 + 23 * n ^ 2 - 42 * n + 24) / 24
// a[n] = the maximum number of regions created by sides and diagonals of n-gon.
TYPE a[MAXN];
void initialize()
{
    a[0] = a[3] = 1, a[1] = a[2] = 0, a[4] = 4;
    for (ll i = 5; i < MAXN; i++)
    {
#ifdef MOD
        a[i] = a[i - 1] * ((TYPE) 5) % MOD;
        a[i] -= a[i - 2] * ((TYPE) 10) % MOD;
        a[i] += a[i - 3] * ((TYPE) 10) % MOD;
        a[i] -= a[i - 4] * ((TYPE) 5) % MOD;
        a[i] = (a[i] + a[i - 5] + MOD) % MOD;
#else
        a[i] = a[i - 1] * ((TYPE) 5)
        a[i] -= a[i - 2] * ((TYPE) 10)
        a[i] += a[i - 3] * ((TYPE) 10)
        a[i] -= a[i - 4] * ((TYPE) 5)
        a[i] += a[i - 5];
#endif
    }
}

template <typename T>
TYPE get_a(T n)
{
    TYPE x = (TYPE) n;
    TYPE x_square = x * x;
    TYPE res;
    res = x_square * x_square;
    res -= x_square * x * ((TYPE) 6);
    res += x_square * ((TYPE) 23);
    res -= x * ((TYPE) 42);
    res += (TYPE) 24;
    res = res / 24;
    return res;
}
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// A007664 - OEIS
// {0, 1, 3, 5, 9, 13, 17, 25, 33, 41, 49, 65, 81, 97, ...}
// number of moves needed to solve the Towers of Hanoi puzzle
// with 4 pegs and n disks
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// A008904 - OEIS
// {1, 1, 2, 6, 4, 2, 2, 4, 2, 8, 8, 8, 6, 8, 2, 8, 8, ...}
// a[n] = final nonzero digit of n!.
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
// {1, 3, 15, 85, 493, 2871, 16731, 97513, 568345, ...}
// Solution to b * (b - 1) = 2 * a * (a - 1) in natural numbers.
// a[n] = the n-th of a in ascending order.
TYPE a[MAXN];
void initialize()
{
    a[0] = 1, a[1] = 3;
#ifdef MOD
    for (ll i = 2; i < MAXN; i++)
        a[i] = (6 * a[i - 1] % MOD - a[i - 2] - 2 + 2 * MOD) % MOD;
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
// {1, 4, 21, 120, 697, 4060, 23661, 137904, 803761, ...}
// Solution to a * (a - 1) = 2 * b * (b - 1) in natural numbers.
// a[n] = the n-th of a in ascending order.
TYPE a[MAXN];
void initialize()
{
    a[0] = 1, a[1] = 4;
#ifdef MOD
    for (ll i = 2; i < MAXN; i++)
        a[i] = (6 * a[i - 1] % MOD - a[i - 2] - 2 + 2 * MOD) % MOD;
#else
    for (ll i = 2; i < MAXN && i <= 25; i++)
        a[i] = 6 * a[i - 1] - a[i - 2] - 2;
    // MAXIMUM 25 for long long
#endif
}
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// A166079 - OEIS
// Related to A185456
// {0, 1, 1, 2, 2, 3, 3, 3, 4, 5, 5, 5, 5, 5, 6, 7, ...}
// Given a row of n pay phones, all initially unused,
// a[n] people can use the pay phones, assuming
//     (1) each always chooses one of the most distant
//         pay phones from those in use already,
//     (2) the first person takes a phone at the end,
//     (3) no people use adjacent phones.
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
// {0, 1, 3, 5, 8, 9, 14, 15, 16, 17, 26, 27, 28, 29, ...}
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
// PE - Problem 32
// Pandigital products
// Products whose multiplicand/multiplier/product identity
// can be written as a 1 through 9 pandigital.
// 138 * 42 = 5796
// 157 * 28 = 4396
// 159 * 48 = 7632
// 1738 * 4 = 6952
// 186 * 39 = 7254
// 1963 * 4 = 7852
// 198 * 27 = 5346
// Only 7 products are pandigital products.
TYPE a[] = {4396, 5346, 5796, 6952, 7254, 7632, 7852};
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// PE - Problem 34
// Digit factorials
// A014080 - OEIS
// Numbers which are equal to the sum of the factorial of their digits.
// 1! + 4! + 5! = 145
// 4! + 0! + 5! + 8! + 5! = 40585
// Only 4 numbers satisfy this nature.
TYPE a[] = {1, 2, 145, 40585};
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// PE - Problem 37
// Double direction truncatable primes
// A020994 - OEIS
// Take 3797 for example:
//     3797, 797, 97, 7 & 3797, 379, 37, 3 are all primes
// Only 15 primes that are double direction truncatable.
TYPE a[] = {2, 3, 5, 7, 23, 37, 53, 73, 313, 317, 373, 797, 3137, 3797, 739397};
// ---------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------------
// PE - Problem 156
// Counting digits
// A216398 - OEIS
// f(x, d) = the total number of digits d that have been
//           written down after the number x has been written
// a[n] = the sum of all the solutions for which f(x, n) == x
TYPE a[] = {1, 22786974071, 73737982962, 372647999625, 741999999540, 100000000000,
            2434703999430, 1876917059570, 15312327487352, 360000000000};
// ---------------------------------------------------------------------------------------------------------------------

