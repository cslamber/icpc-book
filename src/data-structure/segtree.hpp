template<class B> struct Segtree : public B {
    using T = typename B::T;

    size_t n; vector<T> s;
    Segtree(size_t n) : n(n), s(2*n,B::e) {};
    void set(int i, T val) {
        for (s[i += n] = val; i >>= 1;) s[i] = B::op(s[2*i],s[2*i+1]);
    }

    T get(int l, int r) {
        T la = B::e, ra = B::e;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) la = B::op(la, s[l++]);
            if (r & 1) ra = B::op(s[--r], ra);
        }
        return B::op(la, ra);
    }

    vi intervals(int l, int r) {
        deque<int> q;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) la = q.push_back(l++);
            if (r & 1) ra = q.push_front(--r);
        }
        return vi(all(q));
    }
};
