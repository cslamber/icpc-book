tcT using vec = vector<T>;
#define vT vec<T>
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
