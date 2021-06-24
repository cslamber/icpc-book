/** INCLUDE prelude/prelude.hpp */

/** INCLUDE data-structure/segtree.hpp */
/** INCLUDE data-structure/perfect-segtree.hpp */

struct AddInt {
    using T = int;
    const T e = 0;
    T op(T a, T b) { return a + b; }
};

void check_basic() {
    using PST = PerfectSegtree<Segtree<AddInt>>;
    int n = 1000000;
    PST t(n);
    rep(i,0,n) t.set(i, 1);
    int res = t.bsearch_left(200, [](int x) { return x > 20; });
    assert(res == 179);
    res = t.bsearch_right(200, [](int x) { return x > 20000; });
    assert(res == 20201);
}

void subcases() {
    check_basic();
}

