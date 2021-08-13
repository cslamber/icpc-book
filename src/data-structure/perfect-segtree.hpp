template<class Seg> struct PerfectSegtree : Seg {
    using T = typename Seg::T;

    template<class...Args> PerfectSegtree(vT v, Args...args) :
        Seg((v.resize(sbit(bit_width(sz(v)))), v), args...) {}
    template<class...Args> PerfectSegtree(int n) :
        Seg(vT(n), args...) {}

    // return largest l such that cond(query(l,r))
    template<class Lift, class H, class Cond>
    int bsearch_left(int r, Lift lift, H h, Cond cond) {
        typename H::T acc = h.e;
        return yc([&](auto rec, int i, int left, int right) -> int {
            if (left > r) return -1;

            if (right <= r) {
                typename H::T pot = h.op(lift(this->s[i]), acc);

                if (left == right) return cond(pot) ? left : -1;

                if (!cond(pot)) {
                    acc = pot;
                    return -1;
                }
            }

            int mid = (left + right) >> 1;

            Seg::push_down(i, right - left + 1);
            int x = rec(i<<1|1, mid+1, right);
            if (x >= 0) return x;
            return rec(i<<1|0, left, mid);
        })(1, 0, this->n - 1);
    }

    template<class Cond>
    int bsearch_left(int r, Cond cond) {
        return bsearch_left(r, identity, this->m, cond);
    }

    // return smallest r >= l such that cond(query(l,r))
    template<class Lift, class H, class Cond>
    int bsearch_right(int l, Lift Lift, H h, Cond cond) {
        typename H::T acc = h.e;
        return yc([&](auto rec, int i, int left, int right) -> int {
            if (right < l) return -1;

            if (left >= l) {
                typename H::T pot = h.op(acc, lift(this->s[i]));

                if (left == right) return cond(pot) ? right : -1;

                if (!cond(pot)) {
                    acc = pot;
                    return -1;
                }
            }

            int mid = (left + right) >> 1;

            Seg::push_down(i, right - left + 1);
            int x = rec(i<<1|0, left, mid);
            if (x >= 0) return x;
            return rec(i<<1|1, mid+1, right);
        })(1, 0, this->n - 1);
    }

    template<class Cond>
    int bsearch_right(int r, Cond cond) {
        return bsearch_right(r, identity, this->m, cond);
    }
};
