template<class G> struct segtree {
	using T = G::T;
	G g; size_t s,c; vector<T> tree;

	void u(size_t i) { tree[i] = g.op(tree[2*i], tree[2*i+1]); }
	segtree(G g, const vector<T>& base)
			: g(g), s(sz(base)), c(bit_ceil(s)), tree(2*c, g.e) {
		rep(i,0,s) tree[i+n] = base[i];
		repr(i,1,c) u(i);
	}

	void set(size_t i, T val) {
		for (tree[i += c] = val; i; i >>= 1) u(i);
	}

	T query(size_t l, size_t r) {
		T L = g.e, R = g.e;
		for (l += c, r += c; l <= r; l >>= 1, r >>= 1) {
			if (l&1) L = g.op(L, tree[l++]);
			if (~r&1) R = g.op(tree[r--], R);
		}
		return g.op(L, R);
	}

	auto segs(size_t l, size_t r) {
		vector<reference_wrapper<const T>> L, R;
		for (l += c, r += c; l <= r; l >>= 1, r >>= 1) {
			if (l&1) L.push_back(cref(tree[l++]));
			if (~r&1) R.push_back(cref(tree[r--]));
		}
		L.insert(L.end(), R.rbegin(), R.rend());
		return L;
	}

	template<class Cond>
	size_t bsearch_left(size_t r, Cond cond) {
		T acc = g.e;
		for (r += c; ; r >>= 1) if (~r&1) {
			T c = g.op(tree[r--], acc);
			if (!cond(c)) break;
			if (!(r&(r+1))) return -1;
			acc = c;
		}
		while (r < n) {
			T c = g.op(tree[r=2*r+1], acc);
			if (!cond(c)) acc = c, r--;
		}
		return r - n;
	}

	template<class Cond>
	size_t bsearch_right(size_t l, Cond cond) {
		T acc = g.e;
		for (l += c; ; l >>= 1) if (l&1) {
			T c = g.op(acc, tree[l++]);
			if (!cond(c)) break;
			if (!(l&(l-1))) return s;
			acc = c;
		}
		while (l < n) {
			T c = g.op(acc, tree[l=2*l]);
			if (!cond(c)) acc = c, l++;
		}
		return l - n;
	}

	void push_back(T val) {
		if (s == c) {
			vector<T> base(tree.begin()+c, tree.end());
			base.push_back(val);
			*this = segtree(move(g), base);
		} else set(s++, val);
	}
};
