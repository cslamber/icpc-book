template<class M> struct SparseTable : public M {
    // useless, but works with any semigroup rather than just bands
    using T = typename M::T;
    M m;
    vector<vector<T>> t;

    SparseTable(M m, vT data) : m(m), t(bit_width(sz(data)), data) {
        rep(layer,0,sz(t)) {
            int half = sbit(layer);
            for (int g = 0; g < sz(data); g += 2*half) {
                repr(i,g,g+half-1) if (i+1 < sz(data))
                    t[layer][i] = m.op(t[layer][i], t[layer][i+1]);
                rep(i,g+half+1,g+half+half) if (i < sz(data))
                    t[layer][i] = m.op(t[layer][i-1], t[layer][i]);
            }
        }
    }

    T get(int l, int r) {
        if (l > r) return m.e;
        if (l == r) return t[0][l];
        int layer = bit_width(l ^ r) - 1;
        return m.op(t[layer][l], t[layer][r]);
    }
};
