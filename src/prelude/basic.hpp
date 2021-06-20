#define Pb push_back
#define Eb emplace_back

#define Tuple make_tuple
#define Pair make_pair

using vi = vector<int>;

int INF = numeric_limits<int>::max() / 4, ZERO = 0, ONE = 1;
string nl = "\n";

int randrange(int lo, int hi) {
    return uniform_int_distribution<int>(lo, hi-1)(rng); }

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(ref(*this), forward<Args>(args)...); }
};
template<class Fun>
decltype(auto) yc(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun)); }

// bit stuff, some from c++20
nat sbit(int x) { return nat(1) << x; }
int bit_width(nat x) {
    return x ? 64 - __builtin_clzll(x) : 0; }
nat bit_ceil(nat x) {
    return x ? sbit(bit_width(x-1)) : 1; }
int popcount(nat x) {
    return __builtin_popcountll(x); }

