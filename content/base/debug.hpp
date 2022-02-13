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
}

#define dbg(...) do { \
	cerr << __LINE__ << ": [" << #__VA_ARGS__ << "] = "; \
	debug::print(make_tuple(__VA_ARGS__)); \
	cerr << endl; \
	} while (0)
}
#endif
