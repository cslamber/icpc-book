template<class T_> struct AddG {
	using T = T_;
	const T e = 0;
	T plus(T a, T b) { return a + b; }
	T minus(T a, T b) { return a - b; }
};

template<class G = AddG<ll>, uint D = 1> class fenwick {
	using T = G::T; using A = tensor<T, D>;
	G g; A bit;
	void upd(T& x, T v) { x = g.plus(x, v); }
	T query(T& x) { return x; }
	template<uint I, class...Args> void upd(A::slice<I> s, uint i, Args...args) {
		for (; i < sz(s); i |= i+1) upd(s[i], args...);
	}
	template<uint I, class...Args> T sum(A::slice<I> s, uint r, Args...args) {
		T res = g.e; for (; r; r &= r-1) res = g.plus(res, query(s[r-1], args...));
		return res;
	}
	template<uint I, class...Args> T query(A::slice<I> s, uint l, uint r, Args...args) {
		return g.minus(sum(s,r+1,args...), sum(l,args...));
	}
public:
	fenwick(array<uint, T> dim, G g = G()) : g(g), bit(dim, g.e) {}

	template<class...Args> T get(Args...args) { return query(bit, args...); }
	template<class...Args> T set(Args...args) { return upd(bit, args...); }
};
