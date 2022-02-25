#if __cplusplus >= 201703L and defined LOCAL
#include <experimental/type_traits>

namespace debug {
tcT using is_iterator = decltype(declval<T>().begin());
tcT using is_printable = decltype(cerr << declval<T>());
tcT using is_tuple = decltype(get<0>(declval<T>()));
tcT using is_tupable = decltype(declval<T>().tup());

tcT void print(const T& t) {
	if constexpr (experimental::is_detected_v<is_printable, T>) cerr << t;
	else if constexpr (experimental::is_detected_v<is_iterator, T>) {
		string sep; cerr << "{";
		for (const auto& v : t) cerr << sep, sep = ", ", print(v);
		cerr << "}";
	} else if constexpr (experimental::is_detected_v<is_tuple, T>) {
		apply([&](const auto&... ts) {
			string sep; cerr << "{";
			((cerr << sep, sep = ", ", print(ts)), ...);
			cerr << "}";
		}, t);
	} else if constexpr (experimental::is_detected_v<is_tupable, T>) {
		print(t.tup());
	} else cerr << "[??]";
}

#undef dbg
#define dbg(...) do { \
	cerr << __LINE__ << ": [" << #__VA_ARGS__ << "] = "; \
	debug::print(make_tuple(__VA_ARGS__)); \
	cerr << endl; \
	} while (0)

#undef dbgtup
#define dbgtup(...) auto tup() const { return tie(#__VA_ARGS__, __VA_ARGS__)); }

}
#endif
