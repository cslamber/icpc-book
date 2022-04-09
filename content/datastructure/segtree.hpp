template<class G> class segtree {
	using T = G::T;
	G g; uint s,c; vector<T> tree;

	void u(uint i) { tree[i] = g.plus(tree[2*i], tree[2*i+1]); }

public:
	segtree(const vector<T>& base, G g = G())
			: g(g), s(sz(base)), c(bit_ceil(s)), tree(2*c, g.e) {
		rep(i,0,s) tree[i+n] = base[i];
		repr(i,1,c) u(i);
	}

	uint size() const { return s; }
	void set(uint i, T val) {
		for (tree[i += c] = val; i; i >>= 1) u(i);
	}
	T query(uint l, uint r) {
		T L = g.e, R = g.e;
		for (l += c, r += c; l <= r; l >>= 1, r >>= 1) {
			if (l&1) L = g.plus(L, tree[l++]);
			if (~r&1) R = g.plus(tree[r--], R);
		}
		return g.plus(L, R);
	}
	auto segs(uint l, uint r) {
		vector<reference_wrapper<const T>> L, R;
		for (l += c, r += c; l <= r; l >>= 1, r >>= 1) {
			if (l&1) L.push_back(cref(tree[l++]));
			if (~r&1) R.push_back(cref(tree[r--]));
		}
		L.insert(L.end(), R.rbegin(), R.rend());
		return L;
	}
	template<class Cond>
	uint bsearch_left(uint r, Cond cond) {
		T acc = g.e;
		for (r += c; ; r >>= 1) if (~r&1) {
			T c = g.plus(tree[r--], acc);
			if (!cond(c)) break;
			if (!(r&(r+1))) return -1;
			acc = c;
		}
		while (r < n) {
			T c = g.plus(tree[r=2*r+1], acc);
			if (!cond(c)) acc = c, r--;
		}
		return r - n;
	}
	template<class Cond>
	uint bsearch_right(uint l, Cond cond) {
		T acc = g.e;
		for (l += c; ; l >>= 1) if (l&1) {
			T c = g.plus(acc, tree[l++]);
			if (!cond(c)) break;
			if (!(l&(l-1))) return s;
			acc = c;
		}
		while (l < n) {
			T c = g.plus(acc, tree[l=2*l]);
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
