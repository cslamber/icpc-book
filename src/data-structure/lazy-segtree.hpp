/// INCLUDE data-structure/segtree.hpp

template<class M, class Act> struct LazySegtree : public Segtree<M> {
    using T = typename M::T;
    struct MT { T v; };
    struct MF { typename Act::F v; };
    using A = variant<monostate, MT, MF>;

    int h; v<A> a; Act act;
    LazySegtree(const vT& v, M m, Act act) : act(act), Segtree<M>(v, m), h(bit_width(this->n)), a(this->n) {}
    LazySegtree(int n, M m, Act act) : LazySegtree(vT(n, m.e), m, act) {}

    void apply_(int i, A c, int l) {
        match_with(c,
            [&](monostate) { },
            [&](MT t) { this->s[i] = act.mult(t.v, l); if (i < this->n) a[i] = c; },
            [&](MF f) {
                this->s[i] = act.act(f.v, this->s[i], l);
                if (i < this->n) match_with(a[i],
                    [&](monostate) { a[i] = c; },
                    [&](MT t) { a[i] = MT{ act.act(f.v, t.v, 1)}; },
                    [&](MF g) { a[i] = MF{ act.mult(f.v, g.v) }; }
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

    T operator[](int i) {
        push(i); return this->s[i+this->n]; }

    void action(int l, int r, A v) {
        if (l > r) return;
        push(l); push(r);
        this->for_intervals(l, r,
            [&](int i, int k) { apply_(i, v, k); },
            [&](int i, int k) { apply_(i, v, k); });
        push(l); push(r);
        this->build(l); this->build(r);
    }

    template<class F, class H>
    T get(int l, int r, F f, H h) {
        push(l); push(r); return Segtree<M>::get(l, r, f, h); }

    T get(int l, int r) {
        push(l); push(r); return Segtree<M>::get(l, r); }

    void set(int l, int r, T v) {
        action(l, r, MT{v}); }

    void apply(int l, int r, typename Act::F f) {
        action(l, r, MF{f}); }
};
