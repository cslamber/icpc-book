template<class T_> struct Segtree {
    using T = T_;
    int n; vT s;

    Segtree(const vT& x) : n(sz(x)), s(2*n) {
        rep(i,0,n) s[i+n] = x[i];

        repr(i,0,n) s[i] = s[2*i] + s[2*i+1];
    };
    Segtree(int n) : Segtree(vT(n)) {};

    void build(int i) {
        for (i += n; i >>= 1;) s[i] = s[2*i] + s[2*i+1]; }

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

    template<class S = T>
    S get(int l, int r) {
        S la, ra;
        for_intervals(l, r,
            [&](int i, int k) { la = la + S(s[i]); },
            [&](int i, int k) { ra = S(s[i]) + ra; });
        return la + ra;
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
