#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 65600
ll ans;
ll a[MAXN], b[MAXN];

void merge(ll start, ll mid, ll end){
    ll i = start, j = mid + 1, k = 0;
    while (i <= mid && j <= end)
    {
        if(a[i] > a[j])
        {
            b[k++] = a[j++];
            ans += mid - i + 1;
        }
        else
        {
            b[k++] = a[i++];
        }
    }
    while (i <= mid) b[k++] = a[i++];
    while (j <= end) b[k++] = a[j++];
    for (ll l = 0; l < k; l++) a[start + l] = b[l];
}

void inverse_pairs(ll start, ll end)
{
    if (start < end)
    {
        ll mid = start + end >> 1;
        inverse_pairs(start, mid);
        inverse_pairs(mid + 1, end);
        merge(start, mid, end);
    }
}
