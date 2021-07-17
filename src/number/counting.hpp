/// INCLUDE util/modnum.hpp

tcI struct modnum_helpers {
    vI fact, ifact, inv;
    modnum_helpers(size_t n) : fact(n), ifact(n), inv(n) {
        fact[0] = 1;
        rep(i,1,n) fact[i] = fact[i-1] * i;
        ifact[n-1] = Int(1) / fact[n-1];
        repr(i,0,n-1) ifact[i] = ifact[i+1] * (i+1);
        rep(i,1,n) inv[i] = ifact[i] * fact[i-1];
    }

    Int binom(int n, int r) {
        assert(0 <= r && r <= n && n < sz(fact));
        return fact[n] * ifact[r] * ifact[n-r];
    }
};
