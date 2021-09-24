#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
/// INCLUDE defines.hpp
void cases();void read();void solve();void output();void gen();bool check();
signed main(){ios_base::sync_with_stdio(false);cin.tie(nullptr);cout<<setprecision(17);
#ifdef LOCAL_FUZZING
fuzz();
#else
cases();
#endif
}
/// INCLUDE prelude/debug.hpp
/// INCLUDE prelude/basic.hpp
void run(){read();solve();output();}
void fuzz(){Debug::_DEBUG=0;for(int i=0;;++i){if(!(i&0x3ff))cout<<i<<nl;gen();solve();if(check())continue;Debug::_DEBUG=1;debug();solve();return;}}
/// INCLUDE prelude/aggregate.hpp
