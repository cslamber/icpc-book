template<class Seg> struct PerfectSegtree : Seg {
    using T = typename Seg::T;
    PerfectSegtree(int n) : Seg(sbit(bit_width(n))) {}

    // return largest l such that cond(query(l,r))
    template<class Cond>
    int bsearch_left(int r, Cond cond) {
        T acc = Seg::e;
        return yc([&](auto rec, int i, int left, int right) -> int {
            if (r < left) return -1;

            T pot = Seg::op(this->s[i], acc);

            if (right - left == 1) return cond(pot) ? left : -1;

            if (right <= r && !cond(pot)) {
                acc = pot;
                return -1;
            }

            int mid = (left + right) >> 1;

            Seg::push_down(i, right - left);
            int x = rec(i<<1|1, mid, right);
            if (x >= 0) return x;
            return rec(i<<1|0, left, mid);
        })(1, 0, this->n);
    }

    // return smallest r such that cond(query(l,r))
    template<class Cond>
    int bsearch_right(int l, Cond cond) {
        T acc = Seg::e;
        return yc([&](auto rec, int i, int left, int right) -> int {
            if (right < l) return -1;

            T pot = Seg::op(acc, this->s[i]);

            if (right - left == 1) return cond(pot) ? right : -1;

            if (l <= left && !cond(pot)) {
                acc = pot;
                return -1;
            }

            int mid = (left + right) >> 1;

            Seg::push_down(i, right - left);
            int x = rec(i<<1|0, left, mid);
            if (x >= 0) return x;
            return rec(i<<1|1, mid, right);
        })(1, 0, this->n);
    }
};