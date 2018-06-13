class DSU {
public:
    vector<int> p, r;
    virtual void init(int n) {
        p.resize(n+1);
        r.resize(n+1);
        for(int i = 0; i <= n; i++) {
            p[i] = i;
            r[i] = 0;
        }
    }
    virtual int find(int x) {
        return p[x] == x? x: p[x] = find(p[x]);
    }
    virtual bool unite(int x,int y) {
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
    virtual bool same(int x,int y) {
        return find(x)==find(y);
    }
};
