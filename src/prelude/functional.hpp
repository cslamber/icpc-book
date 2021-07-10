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

// for visiting
// https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
