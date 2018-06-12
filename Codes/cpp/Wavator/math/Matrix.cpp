struct Matrix
{
#define type long long
    static const mod = 1000000007;
    int n;
    vector<vector<type> > a;
    Matrix(int n = 0, type dig = 0) : n(n) {
        a = vector<vector<type> >((unsigned int)n, vector<type>(n, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = dig;
    }
    vector<type> operator[](int i) {
        return a[i];
    }
    Matrix operator * (Matrix &b) const
    {
        Matrix res(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    res[i][j] += a[i][k] * b[k][j] % mod, res[i][j] %= mod;
        return res;
    }
    
    void operator *= (Matrix &b){
        *this = (*this) * b;
    }
    
    void operator ^= (long long t) {
        *this = *this ^ t;
    }
    
    Matrix operator^(long long t) const {
        Matrix res(n);
        for(int i = 0; i < n; ++i)
            res[i][i] = 1;
        Matrix tmp = *this;
        for(; t; t >>= 1, tmp = tmp * tmp)
            if (t & 1)
                res = res * tmp;
        return res;
    }

#undef type
};
