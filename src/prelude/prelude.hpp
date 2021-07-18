#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#define int int64_t
using nat = uint64_t;
#define real double

#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define repr(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define repi(i,a,b) for (int i = (a); i <= (b); i++)
#define each(x,y) for (auto& x : (y))

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#define tcT template<class T>
#define tcI template<class Int>
#define tcF template<class F>

tcT int sz(const T& c){ return c.size(); }

void subcases(); bool CONTINUE = true;
void solve();
void precompute();

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << setprecision(17);
    subcases();
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

#define Pb push_back
#define Eb emplace_back

#define Tuple make_tuple
#define Pair make_pair


int INF = numeric_limits<int>::max() / 4, ZERO = 0, ONE = 1;
string nl = "\n";


/// INCLUDE prelude/debug.hpp
/// INCLUDE prelude/basic.hpp

/// INCLUDE util/functional.hpp
