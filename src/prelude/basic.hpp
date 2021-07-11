template<class Int, class Op = multiplies<Int>>
Int Pow(Int base, nat exp, Int one = 1, Op op = Op()) {
    for (; exp; exp >>= 1) {
        if (exp&1) one = op(one, base);
        base = op(base, base);
    }
    return one;
}

int randrange(int lo, int hi) {
    return uniform_int_distribution<int>(lo, hi-1)(rng); }

// bit stuff, some from c++20
nat sbit(int x) { return nat(1) << x; }
int bit_countl(nat x) {
    return x ? __builtin_clzll(x) : 64; }
int bit_countr(nat x) {
    return x ? __builtin_ctzll(x) : 64; }
int bit_width(nat x) {
    return 64 - bit_countl(x); }
int popcount(nat x) {
    return __builtin_popcountll(x); }

// functional stuff

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

// https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template<class T, class... Ts> void match_with(T&& t, Ts &&...fs) {
    visit(overloaded{forward<Ts>(fs)...}, forward<T>(t)); }
