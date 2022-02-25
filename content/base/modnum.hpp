/// INCLUDE complete_operators

template <uint32_t MOD_>
struct modnum {
	using T = modnum;
	using u64 = uint64_t;
	using u32 = uint32_t;
	static const u32 MOD = MOD_;
	u32 v;

	static u32 minv(u32 a, u32 m) {
		a %= m; assert(a);
		return a == 1 ? 1 : m - (u64)minv(m, a) * m / a;
	}

	modnum() : v(0) {}
	modnum(ll _v) { _v %= MOD; v = _v < 0 ? _v + MOD : _v; }
	explicit operator u32() const { return v; }
	friend ostream& operator<<(ostream& out, const T& n) {
		return out << u32(n); }
	friend istream& operator>>(istream& in, T& n) {
		ll v_; in >> v_; n = modnum(v_); return in; }

	bool operator==(const T& a) { return a.v == v; }
	bool operator!=(const T& a) { return a.v != v; }

	T inv() const { modnum r; r.v = minv(v, MOD); return r; }

	T operator+() const { return modnum(*this); }
	T operator-() const { modnum r; r.v = v ? MOD-v : 0; return r; }
	T& operator++() { v++; if (v == MOD) v = 0; return *this; }
	T& operator--() { if (v == 0) v = MOD; v--; return *this; }
	incdec(T)
	T& operator+=(const T& o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
	T& operator-=(const T& o) { v = v - o.v + (v < o.v ? MOD : 0); return *this; }
	T& operator*=(const T& o) { v = (u64)v * o.v % MOD; return *this; }
	T& operator/=(const T& o) { return *this *= o.inv(); }
	binop(T,+,T) binop(T,-,T) binop(T,*,T) binop(T,/,T)

	/* combo helpers */
	static vector<T> fact_, ifact_, inv_;

	static void compute_facts(int n) {
		if (fact_.size() < ++n) { 
			fact_.resize(n *= 2); ifact_.resize(n); inv_.resize(n);
			fact_[0] = 1;
			rep(i,1,n) fact_[i] = fact_[i-1] * i;
			ifact_[n-1] = T(1) / fact_[n-1];
			rep(i,2,n) ifact[n-i] = ifact[n-i+1] * (n-i+1);
			rep(i,1,n) inv_[i] = ifact_[i] * fact_[i-1];
		}
	}

	static T fact(int n) { return compute_facts(n), fact_[n]; }
	static T ifact(int n) { return compute_facts(n), ifact_[n]; }
	static T c(int n, int r) { return fact(n) * ifact(r) * ifact(n-r); }
};

