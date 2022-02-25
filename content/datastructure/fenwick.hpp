template<class G> struct FT {
	using T = G::T;
	G g; vector<T> s;
	FT(size_t n, G g) : g(g), s(n, g.e) {}
	void update(size_t i, T dif) {
		for (; i < sz(s); i |= i+1) s[i] = g.op(s[i], dif);
	}
	T query(size_t i) {
		T r = g.e;
		for (; i; i &= i-1) r = g.op(r, s[i-1]);
		return r;
	}
};
