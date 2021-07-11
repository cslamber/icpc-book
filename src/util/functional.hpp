template<class T, class F> vT vec_init(int n, F f) {
    vT r();
    rep(i,0,n) r.push_back(f(i));
    return r;
}

template<class T, class Op = plus<T>>
vT partials(const vT& o, T&& init = 0, Op op = Op()) {
    vT r(sz(o)+1));
    r[0] = init;
    rep(i,0,sz(o)) r[i+1] = op(r[i], o[i]);
    return r;
}
