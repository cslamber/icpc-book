#define Pb push_back
#define Eb emplace_back

#define Tuple make_tuple
#define Pair make_pair

using vi = vector<int>;

int INF = numeric_limits<int>::max() / 4, ZERO = 0, ONE = 1;
string nl = "\n";

int randrange(int lo, int hi) {
    return uniform_int_distribution<int>(lo, hi-1)(rng); }

// bit stuff, some from c++20
nat sbit(int x) { return nat(1) << x; }
int bit_width(nat x) {
    return x ? 64 - __builtin_clzll(x) : 0; }
int popcount(nat x) {
    return __builtin_popcountll(x); }

// INCLUDE prelude/functional.hpp
