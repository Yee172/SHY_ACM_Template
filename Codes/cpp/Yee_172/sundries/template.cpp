#include <bits/stdc++.h>
#pragma optimize("Ofast")
using namespace std;
#define rep(i, a, n) for (int i = a; i < n; i++)
#define rep_(i, a, n) for (int i = a; i <= n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define per_(i, a, n) for (int i = n; i >= a; i--)
#define FAST ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define square(x) ((x) * (x))
#define summation(x, y) (((x) - (y) + 1) * ((x) + (y)) / 2)
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef pair<int, int> PII;
const ll mod = 1000000007;
const ll mod2inv = 500000004;
const ll inf = 0x3f3f3f3f3f3f3f3f;
ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a;}
ll power(ll a,ll b) {ll r = 1; for(; b; b >>= 1) {if (b & 1) r = r * a; a = a * a;} return r;}
ll powmod(ll a,ll b) {ll r = 1; a %= mod; for(; b; b >>= 1) {if (b & 1) r = r * a % mod; a = a * a % mod;} return r;}
ll inv(ll x) {if (x == 1) return 1; else return (mod - mod / x) * inv(mod % x) % mod;}
ll inv(ll x) {return powmod(x, mod - 2);}
const ll MAXN = 1000005;

int main()
{

    return 0;
}
