/** INCLUDE prelude/prelude.hpp */

/** INCLUDE data-structure/segtree.hpp */
/** INCLUDE data-structure/lazy-segtree.hpp */

void precompute() {}

struct AddInt {
    using T = int;
    const T e = 0;
    T op(T a, T b) { return a + b; }
    T mult(T a, size_t n) { return a * n; }
    using F = monostate;
    T apply(T a, F, size_t) { return a; }
    F compose(F a, F) { return a; }
};

void check_basic() {
    using PST = LazySegtree<AddInt>;
    int n = 1000000;
    PST t(n);
    t.set(1, 0, n);
    int res = t.get(10000, 30201);
    assert(res == 20201);
}

void subcases() {
    check_basic();
}
