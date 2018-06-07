#include <bits/stdc++.h>
using namespace std;

#pragma optimize("-O3")

string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(const bool &b) {
    return (b ? "true" : "false");
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(const A &v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first)
            res += ", ";
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef Wavator

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);

#else

#define debug(...) 42;

#define cerr if (false) cout

#endif

#define rep(i, a, b) for (auto i = (a); i < (b); ++i)
#define per(i, a, b) for (auto i = (b) - 1; i >= a; --i)

#define pb push_back

typedef long long ll;
typedef double db;
typedef vector <int> vi;
typedef vector <ll> vl;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;

template <typename T>
inline void _read(T &x) {
    cin >> x;
}

template <typename A, typename B>
inline void _read(pair<A, B> &x) {
    _read(x.first);
    _read(x.second);
}

template <typename T>
inline void _read(vector<T> &x) {
    for (auto &v: x)
        _read(v);
}


void R() {}
template <typename T, typename...U>
void R(T &head, U&...tail) {
    _read(head);
    R(tail...);
}

#define endl '\n'

template <typename T>
inline void _write(const T &x) {
    cout << x << ' ';
}

template <typename A, typename B>
inline void _write(const pair<A, B>&x) {
    _write(x.first);
    _write(x.second);
}

template <typename T>
inline void _write(const vector<T> &in) {
    for (const auto &x: in)
        _write(x);
}

void W() {cout << endl;}
template <typename T, typename...U>
void W(const T &head, const U&...tail) {
    _write(head);
    W(tail...);
}

#define my_sort_unique(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))

#define my_unique(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))

#define fi first

#define se second


int main() {
#ifdef Wavator
    freopen("test.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);



    return 0;
}
