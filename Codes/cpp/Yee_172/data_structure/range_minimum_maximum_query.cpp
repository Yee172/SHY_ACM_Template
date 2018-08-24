#include <bits/stdc++.h>
using namespace std;

#define MAXN 50050
#define MAXLOGN 20

template <typename T>
class RMQ
{
public:
    RMQ() {}
    RMQ(function<T(T, T)> M) : M(M) {}

    inline T *operator[](int i) {return dp[i];}

    inline void init(T a[], int len, int start=1)
    {
        for (int i = 1, k = start; i <= len; i++, k++)
            dp[i][0] = a[k];
        for (int j = 1, k = 2; k <= len; j++, k <<= 1)
            for (int i = 1; i + k - 1 <= len; i++)
                dp[i][j] = M(dp[i][j - 1], dp[i + (k >> 1)][j - 1]);
    }

    inline T query(int left, int right)
    {
        int k = 0;
        for (; 1 << k + 1 <= right - left + 1; k++);
        return M(dp[left][k], dp[right - (1 << k) + 1][k]);
    }
private:
    function<T(T, T)> M = [&](const T&x, const T&y) {return x > y ? x : y;};
    T dp[MAXN][MAXLOGN];
};
