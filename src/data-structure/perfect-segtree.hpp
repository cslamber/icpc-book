template<class Seg> struct PerfectSegtree : Seg {
    using T = typename Seg::T;
    PerfectSegtree(vT v) : Seg((v.resize(sbit(bit_width(sz(v)))), v)) {}
    PerfectSegtree(int n) : Seg(vT(n)) {}

    // return largest l such that cond(query(l,r))
    template<class Cond, class S = T>
    int bsearch_left(int r, Cond cond) {
        S acc;
        return yc([&](auto rec, int i, int left, int right) -> int {
            if (left > r) return -1;

            if (right <= r) {
                S pot = S(this->s[i]) + acc;

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

    // return smallest r >= l such that cond(query(l,r))
    template<class S = T, class Cond>
    int bsearch_right(int l, Cond cond) {
        S acc;
        return yc([&](auto rec, int i, int left, int right) -> int {
            if (right < l) return -1;

            if (left >= l) {
                S pot = acc + S(this->s[i]);

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
};
