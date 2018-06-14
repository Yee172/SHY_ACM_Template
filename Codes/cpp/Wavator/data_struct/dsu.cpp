class DSU {
public:
    DSU(int n = 0){init(n);}
    vector<int> p, r;
    void init(int n) {
        p.resize(n+1);
        r.resize(n+1);
        iota(p.begin(),p.end(),0);
        fill(r.begin(),r.end(),0);
    }
    int find(int x) {
        if (p[x] == x)
            return x;
        return p[x] = find(p[x]);
    }
    inline bool unite(int x,int y) {
        x = find(x);
        y = find(y);
        if(x == y)
            return false;
        if(r[x] < r[y])
            p[x] = y;
        else {
            p[y] = x;
            if(r[x]==r[y])
                r[x]++;
        }
        return true;
    }
    inline bool same(int x,int y) {
        return find(x)==find(y);
    }
};
