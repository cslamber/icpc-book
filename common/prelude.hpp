#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

// common defines
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define repr(i,a,b) for (int i = (b-1); i >= a; i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define tcT template<class T>
#define L1(...) ([&](auto& it){ return __VA_ARGS__; })
#define L1c(...) ([&](const auto& it){ return __VA_ARGS__; })
#define L2(...) ([&](auto& it, auto& ot){ return __VA_ARGS__; })

// common functions & types
auto sz = L1c(it.size());
tcT using vec = vector<T>;
using ll = int64_t;
using nat = uint64_t;
using vi = vec<int>;
using vl = vec<ll>;
using pll = pair<ll,ll>;

// framework
void subcases();

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << setprecision(17);
	subcases();
}

// debug
#define dbg(...) do {} while (0)

#if __cplusplus >= 201703L and defined LOCAL
#include <experimental/type_traits>

namespace debug {

tcT using is_iterator = decltype(declval<T>().begin());
tcT using is_printable = decltype(cerr << declval<T>());

tcT void print(const T& t) {
	if constexpr (experimental::is_detected_v<is_printable, T>) cerr << t;
	else if constexpr (experimental::is_detected_v<is_iterator, T>) {
		string sep; cerr << "{";
		for (const auto& v : t) cerr << sep, sep = ", ", print(v);
		cerr << "}";
	} else if constexpr (experimental::is_detected_v<tuple_size, T>) {
		apply([&](const auto&... ts) {
			string sep; cerr << "{";
			((cerr << sep, sep = ", ", print(ts)), ...);
			cerr << "}";
		}, t);
	} else cerr << "[??]";
	cerr << " ";
	return *this;
}

#define dbg(...) do { \
	cerr << __LINE__ << ": [" << #__VA_ARGS << "] = "; \
	debug::print(make_tuple(__VA_ARGS__)); \
	cerr << endl; \
	} while (0)
}
#endif

// util
const char nl = '\n';
auto setmax = [](auto& d, auto s){ if (d < s) d = s; }
auto setmin = [](auto& d, auto s){ if (s < d) d = s; }

// backported from c++20
int countl_zero(nat x) { return x ? __builtin_clzll(x) : 64; }
int countr_zero(nat x) { return x ? __builtin_ctzll(x) : 64; }
int bit_width(nat x) { return 64 - bit_countl(x); }
int popcount(nat x) { return __builtin_popcountll(x); }

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

// https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template<class T, class... Ts> void match_with(T&& t, Ts &&...fs) {
	visit(overloaded{forward<Ts>(fs)...}, forward<T>(t)); }

// generic stuff
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
