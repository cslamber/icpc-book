template<class M> struct Segtree : public M {
    using T = typename M::T;

    int n; vec<T> s;
    Segtree(int n) : n(n), s(2*n,M::e) {};

    void build(int i) {
        for (i += n; i >>= 1;) s[i] = M::op(s[2*i],s[2*i+1]); }

    void set(int i, T val) {
        s[i+n] = val; build(i); }

    // outside in
    template<class Left, class Right>
    void for_intervals(int l, int r, Left left, Right right) {
        int k = 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l & 1) left(l++, k);
            if (r & 1) right(--r, k);
        }
    }

    T get(int l, int r) {
        T la = M::e, ra = M::e;
        for_intervals(l, r,
            [&](int i, int k) { la = M::op(la, s[i]); },
            [&](int i, int k) { ra = M::op(s[i], ra); });
        return M::op(la, ra);
    }

    vi intervals(int l, int r) {
        vec<int> left, right;
        for_intervals(l, r,
            [&](int i, int k) { left.push_back(i); },
            [&](int i, int k) { right.push_back(i); });
        left.insert(left.end(), rall(right));
        return left;
    }

    void push_down(int i, int k) {}
};
