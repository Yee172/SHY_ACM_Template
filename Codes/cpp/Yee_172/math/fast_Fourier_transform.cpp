#include <bits/stdc++.h>
using namespace std;

namespace FFT
{
    typedef int TYPE;
    typedef long double db;
    const db PI = acosl(-1.0);

    struct cp
    {
        db real, image;
        cp() { real = image = 0.0; }
        cp(db real, db image) : real(real), image(image) {}
    };

    inline cp operator+(cp a, cp b) { return cp(a.real + b.real, a.image + b.image); }
    inline cp operator-(cp a, cp b) { return cp(a.real - b.real, a.image - b.image); }
    inline cp operator*(cp a, cp b)
    { return cp(a.real * b.real - a.image * b.image, a.real * b.image + a.image * b.real); }
    inline cp conjugate(cp a) { return cp(a.real, -a.image); }

    int base = 1;
    vector<cp> roots = {{0, 0}, {1, 0}};
    vector<int> rev = {0, 1};

    inline void set_base(int new_base)
    {
        if (new_base <= base) return;
        rev.resize(static_cast<unsigned long>(1 << new_base));
        roots.resize(static_cast<unsigned long>(1 << new_base));
        for (int i = 0; i < (1 << new_base); i++)
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << new_base - 1);
        while (base < new_base)
        {
            db theta = 2 * PI / (1 << base + 1);
            for (int i = 1 << base - 1; i < (1 << base); i++)
            {
                roots[i << 1] = roots[i];
                db theta_i = theta * (2 * i + 1 - (1 << base));
                roots[i << 1 | 1] = cp(cosl(theta_i), sinl(theta_i));
            }
            base++;
        }
    }

    inline void fft(vector<cp> &a, int size = -1)
    {
        if (size < 0) size = static_cast<int>(a.size());
        assert((size & size - 1) == 0);
        int zeros = __builtin_ctz(size);
        set_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < size; i++)
            if (i < (rev[i] >> shift))
                swap(a[i], a[rev[i] >> shift]);
        for (int k = 1; k < size; k <<= 1)
            for (int i = 0; i < size; i += 2 * k)
                for (int j = 0; j < k; j++)
                {
                    cp z = a[i + j + k] * roots[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
    }

    vector<cp> fa;

    inline vector<TYPE> multiply(vector<TYPE> &a, vector<TYPE> &b)
    {
        int need = static_cast<int>(a.size() + b.size() - 1);
        int new_base = 0;
        for (; (1 << new_base) < need; new_base++);
        set_base(new_base);
        int size = 1 << new_base;
        if (size > static_cast<int>(fa.size())) fa.resize(static_cast<unsigned long>(size));
        for (int i = 0; i < size; i++)
        {
            db real = static_cast<db>(i < static_cast<int>(a.size()) ? a[i] : 0);
            db image = static_cast<db>(i < static_cast<int>(b.size()) ? b[i] : 0);
            fa[i] = cp(real, image);
        }
        fft(fa, size);
        cp r(0, -0.25 / size);
        for (int i = 0; i <= (size >> 1); i++)
        {
            int j = size - i & size - 1;
            cp z = (fa[j] * fa[j] - conjugate(fa[i] * fa[i])) * r;
            if (i != j) fa[j] = (fa[i] * fa[i] - conjugate(fa[j] * fa[j])) * r;
            fa[i] = z;
        }
        fft(fa, size);
        vector<TYPE> res(static_cast<unsigned long>(need));
        for (int i = 0; i < need; i++) res[i] = static_cast<TYPE>(fa[i].real + 0.5);
        return res;
    }
}
