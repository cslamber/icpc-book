// https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template<class T, class... Ts> void match_with(T&& t, Ts &&...fs) {
	visit(overloaded{forward<Ts>(fs)...}, forward<T>(t)); }