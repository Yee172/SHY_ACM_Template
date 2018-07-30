#include <bits/stdc++.h>
using namespace std;

template <typename T_key, typename T_value>
class CartesianTree
{
public:
    struct node
    {
        T_key key;
        T_value value;
        int index;
        bool operator < (const node &b) { return key < b.key; }
    };
    vector<int> left_child, right_child, stack, size;
    int root;
    vector<node> member;
    explicit CartesianTree(int n) : n(n)
    {
        resize(left_child, n, -1);
        resize(right_child, n, -1);
        resize(stack, n);
        member.resize(static_cast<unsigned long>(n));
    }

    inline void initialize() { for (int i = 0; i < n; i++) left_child[i] = right_child[i] = -1; }

    node & operator [] (const int i) { return member[i]; }

    inline void build(const T_key * key, const T_value * value, const int key_start=1, const int value_start=1)
    {
        for (int i = 0, j = key_start, k = value_start; i < n; i++)
            member[i].key = key[j++], member[i].value = value[k++], member[i].index = i;
        sort(member.begin(), member.end());
        int top = 0, now = -1;
        for (int i = 0; i < n; i++)
        {
            for (now = top; now && member[stack[now - 1]].value < member[i].value; now--);
            if (now) right_child[member[stack[now - 1]].index] = member[i].index;
            if (now < top) left_child[member[i].index] = member[stack[now]].index;
            stack[now++] = i;
            top = now;
        }
        root = member[stack[0]].index;
    }

    void get_size()
    {
        resize(size, n);
        _dfs(root);
    }
protected:
    int n;

    template <typename T>
    inline void resize(vector<T> &a, const int n, const int x=0) { a.resize(static_cast<unsigned long>(n), x); }

    int _dfs(int root)
    {
        int result = 1;
        if (left_child[root] != -1) result += _dfs(left_child[root]);
        if (right_child[root] != -1) result += _dfs(right_child[root]);
        return size[root] = result;
    }
};
