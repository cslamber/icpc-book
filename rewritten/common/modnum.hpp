template <uint32_t MOD> struct modnum {
	using T = modnum;
	using u64 = uint64_t;
	using u32 = uint32_t;
	u32 v;

	static u32 minv(u32 a, u32 m) {
		a %= m;
		assert(a);
		return a == 1 ? 1 : u32(m - (u64)minv(m, a) * m / a);
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
	T& operator+=(const T& o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
	T& operator-=(const T& o) { v = v - o.v + (v < o.v ? MOD : 0); return *this; }
	T& operator*=(const T& o) { v = u32((u64)v * o.v % MOD); return *this; }
	T& operator/=(const T& o) { return *this*=o.inv(); }

	T operator++(signed) { modnum r(*this); ++(*this); return r; }
	T operator--(signed) { modnum r(*this); --(*this); return r; }
	T operator+(const T& a) const { return modnum(*this) += a; }
	T operator-(const T& a) const { return modnum(*this) -= a; }
	T operator*(const T& a) const { return modnum(*this) *= a; }
	T operator/(const T& a) const { return modnum(*this) /= a; }
};

