#define int int64_t
using nat=uint64_t;
using db=double;
using ldb=long double;
tcT using v=vector<T>;
#define vT v<T>
using vi=v<int>;
using pii=pair<int,int>;
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define repr(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define repi(i,a,b) for(int i=(a);i<=(b);++i)
#define each(x,y) for(auto&x:(y))
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define tcT template<class T>
#define tcTs template<class...Ts>
#define tcF template<class F>
tcT int sz(const T&c){return c.size();}
#define Pb push_back
#define Eb emplace_back
#define Tuple make_tuple
#define Pair make_pair
const int INF=numeric_limits<int>::max()/4,ZERO=0,ONE=1;
const char nl='\n';
