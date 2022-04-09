#include <bits/stdc++.h>
using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define repr(i,a,b) for (int i = (b-1); i >= a; i--)
#define all(x) (x).begin(), (x).end()
#define tcT template<class T>
#define L1(...) ([&](auto& it){ return __VA_ARGS__; })

using ll = long long; using ull = unsigned ll;
using db = double; using uint = unsigned int;
using vi = vector<int>; using pi = pair<int,int>;
using vl = vector<ll>; using pl = pair<ll,ll>;
using vu = vector<uint>; using pu = pair<uint,uint>;

tcT uint sz(const T& t) { return t.size(); }
tcT auto operator+(vector<T>& v, uint i) { return v.begin() + i; }
tcT auto operator+(const vector<T>& v, uint i) { return v.cbegin() + i; }
tcT auto operator-(vector<T>& v, uint i) { return v.end() - i; }
tcT auto operator-(const vector<T>& v, uint i) { return v.cend() - i; }

void subcases();
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << setprecision(17);
	subcases();
}

#define dbg(...) do {} while (0)
#define dbgtup(...)

const char nl = '\n';
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
ll randint(ll lo, ll hi) { return uniform_int_distribution<ll>(lo,hi)(rng); }
tcT void setmax(T& d, T s) { if (d < s) d = s; }
tcT void setmin(T& d, T s) { if (s < d) d = s; }

// backported from c++20
uint countl_zero(ull x) { return x ? __builtin_clzll(x) : 64; }
uint countr_zero(ull x) { return x ? __builtin_ctzll(x) : 64; }
uint bit_width(ull x) { return 64 - countl_zero(x); }
ull sbit(uint x) { return ull(1) << x; }
ull bit_floor(ull x) { return sbit(bit_width(x)-1); }
ull bit_ceil(ull x) { return sbit(bit_width(x-1)); }
uint popcount(ull x) { return __builtin_popcountll(x); }

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class F> struct y_combinator_result {
	F f; tcT explicit y_combinator_result(T&&f) : f(forward<T>(f)) {}
	template<class...Ts> decltype(auto) operator()(Ts&&...ts) {
		return f(ref(*this), forward<Ts>(ts)...); }
};

template<class F> decltype(auto) yc(F&&f) {
	return y_combinator_result<decay_t<F>>(forward<F>(f)); }

tcT pl bsearch(ll lo, ll hi, T f) {
	while (hi - lo > 1) {
		ll m = lo + hi >> 1;
		(f(m) ? hi : lo) = m;
	} return {lo, hi};
}
template<class T, class Op = multiplies<T>>
T Pow(T b, ull e, T o = 1, Op op = Op()) {
	for (; e; e >>= 1) {
		if (e&1) o = op(o, b);
		b = op(b, b);
	} return o;
}
tcT auto cmp_by(T t) {
	return [=](auto i, auto j) { return t(i) < t(j); };
}
