#define vT vec<T>

tcT struct vec : public vector<T> {
    using vector<T>::vector;

    tcF static auto init(int n, F f) {
        vec<decltype(f())> r;
        rep(i,0,n) r.Eb(f());
        return r;
    }

    tcF auto map(F f) const {
        vec<decltype(f(this->at(0)))> r;
        each(x, *this) r.Eb(f(x));
        return r;
    }

    template<class S = T, class F = plus<T>> auto fold(S init, F f = F()) const {
        vec<decltype(f(init,this->at(0)))> r { init };
        each(x, *this) r.Pb(init = f(init, x));
        return r;
    }

    vT copy() const { return vT(*this); }
    vT take(int i) const { return vT(this->cbegin(), this->cbegin() + i); }
    vT drop(int i) const { return vT(this->cbegin() + i, this->cend()); }
    vT reverse() const { return vT(this->crbegin(), this->crend()); }
    vT& pb(T x) { this->push_back(x); return *this; }
    vT sort() const { vT r(*this); std::sort(all(r)); return r; }

    vT append_front(const vT& front) const {
        vT r(front);
        each(x, *this) r.pb(x);
        return r;
    }
};

using vi = vec<int>;
#define vI vec<Int>

template<class T> T read(void) { T x; cin >> x; return x; }

template<class T, class F> T bsearch_real(T lo, T hi, int N, F cond) {
    rep(i,0,N) {
        T mid = (lo + hi) / 2;
        if (cond(mid)) hi = mid;
        else lo = mid;
    }
    return (lo + hi) / 2;
}

tcF int bsearch(int lo, int hi, F cond) {
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (cond(mid)) hi = mid;
        else lo = mid+1;
    }
    return hi;
}

tcT void setmax(T& dest, T src) {
    if (dest < src) dest = src; }

tcT void setmin(T& dest, T src) {
    if (src < dest) dest = src; }
