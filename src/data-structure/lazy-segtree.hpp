/** INCLUDE data-structure/segtree.hpp */

template<class M> struct LazySegtree : public Segtree<M> {
    struct MT { typename M::T v; };
    struct MF { typename M::F v; };
    using A = variant<monostate, MT, MF>;

    int h; vec<A> a;
    LazySegtree(int n) : Segtree<M>(n), h(bit_width(n)), a(n) {}

    void apply_(int i, A c, int l) {
        match_with(c,
            [&](monostate) { },
            [&](MT t) { this->s[i] = M::mult(t.v, l); if (i < this->n) a[i] = c; },
            [&](MF f) {
                this->s[i] = M::apply(this->s[i], f.v, l);
                if (i < this->n) match_with(a[i],
                    [&](monostate) { a[i] = c; },
                    [&](MT t) { a[i] = MT{M::apply(t.v, f.v, 1)}; },
                    [&](MF g) { a[i] = MF{M::compose(f.v, g.v)}; }
                );
            }
        );
    }

    void push_down(int j, int k) {
        if (j >= this->n || !a[j].index()) return;
        apply_(j<<1|0, a[j], k>>1);
        apply_(j<<1|1, a[j], k>>1);
        a[j] = A();
    }

    void push(int i) {
        i += this->n; for (int b = h; b; b--) push_down(i >> b, sbit(b)); }
    
    void action(A v, int l, int r) {
        push(l); push(r-1);
        this->for_intervals(l, r,
            [&](int i, int k) { apply_(i, v, k); },
            [&](int i, int k) { apply_(i, v, k); });
        push(l); push(r-1);
        this->build(l); this->build(r-1);
    }

    typename M::T get(int l, int r) {
        push(l); push(r-1); return Segtree<M>::get(l, r); }

    void set(typename M::T v, int l, int r) {
        action(MT{v}, l, r); }

    void apply(typename M::F a, int l, int r) {
        action(MF{a}, l, r); }
};
