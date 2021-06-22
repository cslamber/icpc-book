// INCLUDE data-structure/segtree.hpp

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