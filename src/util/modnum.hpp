template <uint32_t MOD>
struct modnum {
	using u64 = uint64_t;
	using u32 = uint32_t;
	u32 v;

	static u32 minv(u32 a, u32 m) {
		a %= m;
		assert(a);
		return a == 1 ? 1 : u32(m - u64(minv(m, a)) * u64(m) / a);
	}

	modnum() : v(0) {}
	modnum(int _v) { _v %= MOD; v = _v < 0 ? _v + MOD : _v; }
	explicit operator uint32_t() const { return v; }
	friend std::ostream& operator<<(std::ostream& out, const modnum& n) {
		return out << u32(n); }
	friend std::istream& operator>>(std::istream& in, modnum& n) {
		int v_; in >> v_; n = modnum(v_); return in; }

	bool operator==(const modnum& a) { return a.v == v; }
	bool operator!=(const modnum& a) { return a.v != v; }

	modnum inv() const {
		modnum r; r.v = minv(v, MOD); return r; }

	modnum operator+() const {
		return modnum(*this); }
	modnum operator-() const {
		modnum r; r.v = v ? MOD-v : 0; return r; }
	modnum& operator++() {
		v++; if (v == MOD) v = 0; return *this; }
	modnum& operator--() {
		if (v == 0) v = MOD; v--; return *this; }
	modnum& operator+=(const modnum& o) {
		v += o.v; if (v >= MOD) v -= MOD; return *this; }
	modnum& operator-=(const modnum& o) {
        v = v - o.v + (v < o.v ? MOD : 0); return *this; }
	modnum& operator*=(const modnum& o) {
		v = u32(u64(v) * u64(o.v) % MOD); return *this; }

	modnum& operator/=(const modnum& o) { return *this*=o.inv(); }
	modnum operator++(int32_t) { modnum r(*this); ++(*this); return r; }
	modnum operator--(int32_t) { modnum r(*this); --(*this); return r; }
	modnum operator+(const modnum& a) const { return modnum(*this) += a; }
	modnum operator-(const modnum& a) const { return modnum(*this) -= a; }
	modnum operator*(const modnum& a) const { return modnum(*this) *= a; }
	modnum operator/(const modnum& a) const { return modnum(*this) /= a; }
};
