template<class M> struct Segtree : public M {
    using T = typename M::T;

    int n; vector<T> s;
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
        vector<int> left, right;
        for_intervals(l, r,
            [&](int i, int k) { left.push_back(i); },
            [&](int i, int k) { right.push_back(i); });
        left.insert(left.end(), rall(right));
        return left;
    }
};

template<class M> struct LazySegtree : public M {
    using MT = typename M::T;
    using MF = typename M::F;
    using A = variant<monostate, MT, MF>;
    A aset(MT v) { return A(in_place_index<1>, v); }
    A aact(MF v) { return A(in_place_index<2>, v); }

    int h; vector<A> a; Segtree<M> s;
    LazySegtree(int n) : s(n), h(bit_width(n)), a(n) {}

    void apply_(int i, A c, int l) {
        ordered_visit(c,
            [&](monostate) { },
            [&](MT t) { s.s[i] = M::mult(t, l); if (i < s.n) a[i] = c; },
            [&](MF f) {
                s.s[i] = M::apply(s.s[i], f, l);
                if (i < s.n) ordered_visit(a[i],
                    [&](monostate) { a[i] = c; },
                    [&](MT t) { a[i] = aset(M::apply(t, f, 1)); },
                    [&](MF g) { a[i] = aact(M::compose(f, g)); }
                );
            }
        );
    }

    void push(int i) {
        i += s.n;
        for (int b = h; b; b--) {
            int j = i >> b;
            apply_(j<<1|0, a[j], sbit(b-1));
            apply_(j<<1|1, a[j], sbit(b-1));
            a[j] = A();
        }
    }
    
    void action(A v, int l, int r) {
        push(l); push(r-1);
        s.for_intervals(l, r,
            [&](int i, int k) { apply_(i, v, k); },
            [&](int i, int k) { apply_(i, v, k); });
        push(l); push(r-1);
        s.build(l); s.build(r-1);
    }

    MT get(int l, int r) {
        push(l); push(r-1);
        return s.get(l, r);
    }

    void set(MT v, int l, int r) {
        action(aset(v), l, r); }

    void apply(MF a, int l, int r) {
        action(aact(a), l, r); }
};