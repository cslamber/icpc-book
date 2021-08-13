/// INCLUDE data-structure/augment.hpp

template<class M, bool perfect = false> struct Segtree {
    using T = typename M::T;
    int n; vT s;

    M m;

    Segtree(const vT& x, M m) : m(m), n(sz(x)), s(2*n) {
        rep(i,0,n) s[i+n] = x[i];

        repr(i,0,n) s[i] = m.op(s[2*i], s[2*i+1]);
    };
    Segtree(int n, M m) : Segtree(vT(n, m.e), m) {};

    void build(int i) {
        for (i += n; i >>= 1;) s[i] = m.op(s[2*i], s[2*i+1]); }

    void set(int i, T val) { s[i+n] = val; build(i); }

    T operator[](int i) const { return s[i+n]; }

    // outside in
    template<class Left, class Right>
    void for_intervals(int l, int r, Left left, Right right) {
        int k = 1; r++;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l & 1) left(l++, k);
            if (r & 1) right(--r, k);
        }
    }

    tcF void for_intervals(int l, int r, F f) {
        for_intervals(l, r, f, f); }

    T get(int l, int r) {
        T la = m.e, ra = m.e;
        for_intervals(l, r,
            [&](int i, int k) { la = m.op(la, s[i]); },
            [&](int i, int k) { ra = m.op(s[i], ra); });
        return m.op(la, ra);
    }

    template<class F, class H>
    typename H::T get(int l, int r, F f, H h) {
        typename H::T la = h.e, ra = h.e;
        for_intervals(l, r,
            [&](int i, int k) { la = h.op(la, f(s[i])); },
            [&](int i, int k) { ra = h.op(f(s[i]), ra); });
        return h.op(la, ra);
    }

    vi intervals(int l, int r) {
        vi left, right;
        for_intervals(l, r,
            [&](int i, int k) { left.push_back(i); },
            [&](int i, int k) { right.push_back(i); });
        left.insert(left.end(), rall(right));
        return left;
    }

    void push_down(int i, int k) {}
};
