class LiChao {
private:
    const static int ninf = numeric_limits<int>::min();

    struct Line {
        int m = 0, b = ninf;
        int operator()(int x) const { return m * x + b; }
    };

    struct Node {
        Line v;
        unique_ptr<Node> l, r;
    };

    using N = unique_ptr<Node>;

    void InsertLineKnowingly(N &n, int tl, int tr, Line x) {
        if (!n) n.reset(new Node());
        if (n->v(tl) < x(tl)) swap(n->v, x);
        if (tl == tr || n->v(tr) >= x(tr)) return;
        int mid = (tl + tr) >> 1;
        if (n->v(mid) > x(mid)) {
            InsertLineKnowingly(n->r, mid + 1, tr, x);
        } else {
            swap(n->v, x);
            InsertLineKnowingly(n->l, tl, mid, x);
        }
    }

    void InsertLine(N &n, int tl, int tr, int l, int r, Line x) {
        if (tr < l || r < tl || tl > tr || l > r) return;
        if (!n) n.reset(new Node());
        if (l <= tl && tr <= r) return InsertLineKnowingly(n, tl, tr, x);
        int mid = (tl + tr) >> 1;
        InsertLine(n->l, tl, mid, l, r, x);
        InsertLine(n->r, mid + 1, tr, l, r, x);
    }

    void Query(N &n, int tl, int tr, int x, int& acc) {
        if (!n) return;
        setmax(acc, n->v(x));
        if (tl == tr) return;
        int mid = (tl + tr) >> 1;
        if (x <= mid) Query(n->l, tl, mid, x, acc);
        else Query(n->r, mid + 1, tr, x, acc);
    }

    unique_ptr<Node> root;

public:
    int lb, ub;
    LiChao(int lb, int ub) : lb(lb), ub(ub) {}

    void InsertLine(int l, int r, int m, int b) {
        return InsertLine(root, lb, ub, l, r, {m, b});
    }

    int Query(int x) {
        int res = ninf;
        Query(root, lb, ub, x, res);
        return res;
    }
};
