#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define repr(i,a,b) for (int i = (b-1); i >= a; i--)
#define all(x) (x).begin(), (x).end()
#define tcT template<class T>
#define L1(...) ([&](auto& it){ return __VA_ARGS__; })
#define L1c(...) ([&](const auto& it){ return __VA_ARGS__; })
#define L2(...) ([&](auto& it, auto& ot){ return __VA_ARGS__; })

tcT size_t sz(const T& t) { return t.size() }
using ll = int64_t;
using nat = uint64_t;
using vi = vector<int>;
using vl = vector<ll>;
using pll = pair<ll,ll>;

void subcases();

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << setprecision(17);
	subcases();
}

#define dbg(...) do {} while (0)

const char nl = '\n';
tcT setmax(T& d, T s) { if (d < s) d = s; }
tcT setmin(T& d, T s) { if (s < d) d = s; }

// backported from c++20
int countl_zero(nat x) { return x ? __builtin_clzll(x) : 64; }
int countr_zero(nat x) { return x ? __builtin_ctzll(x) : 64; }
int bit_width(nat x) { return 64 - countl_zero(x); }
int popcount(nat x) { return __builtin_popcountll(x); }
nat sbit(int x) { return (nat)1 << x; }

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
tcF struct y_combinator_result {
	F f;
	tcT explicit y_combinator_result(T &&f): f(forward<T>(f)) {}
	template<class ...Args>
	decltype(auto) operator()(Args &&...args) {
		return f(ref(*this), forward<Args>(args)...); }
};

tcF decltype(auto) yc(F &&f) {
	return y_combinator_result<decay_t<F>>(forward<F>(f)); }

tcT T identity(T&& x) { return forward<T>(x); }

tcT pll bsearch(ll lo, ll hi, T f) {
	while (hi - lo > 1) {
		ll m = lo + hi >> 1;
		(f(m) ? hi : lo) = m;
	}
	return {lo, hi};
}

template<class T, class Op = multiplies<T>>
T Pow(T base, nat exp, T one = 1, Op op = Op()) {
	for (; exp; exp >>= 1) {
		if (exp & 1) one = op(one, base);
		base = op(base, base);
	}
	return one;
}
