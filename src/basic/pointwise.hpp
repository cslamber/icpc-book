template<class C, class E = C::value_type> struct pointwise : public C {
    #define make_op(op) \
    friend C& operator op= (C& x, const C& y) { \
        rep(i,0,sz(x)) x[i] op = y[i]; return x; } \
    friend C operator op (const C& x, const C& y) { \
        return C(x) op= y; } \
    friend C& operator op= (C& x, const E& y) { \
        rep(i,0,sz(x)) x[i] op= y; return x; } \
    friend C operator op (const C& x, const E& y) { \
        return C(x) op= y; }

    make_op(+) make_op(-) make_op(*) make_op(/) make_op(%)
    make_op(&) make_op(|) make_op(^) make_op(<<) make_op(>>)
    #undef make_op
};
