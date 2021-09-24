mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int lo,int hi){return uniform_int_distribution<int>(lo,hi)(rng);}
tcT void setmax(T&dest,T src){if(dest<src)dest=src;}
tcT void setmin(T&dest,T src){if(src<dest)dest=src;}
template<class T,class Op=multiplies<T>>T Pow(T b,nat e,T o=1,Op op=Op()){for(;e;e>>=1){if(e&1)o=op(o,b);b=op(b,b);}return o;}
tcF pii bsearch(int lo,int hi,F f){while(hi-lo>1)(f(lo+hi>>1)?hi:lo)=lo+hi>>1;return{lo,hi};}
tcF pii bsearch_db(db lo,db hi,int n,F f){rep(i,0,n)(f((lo+hi)/2)?hi:lo)=(lo+hi)/2;return(lo+hi)/2;}
tcF pii tsearch_db(db lo,db hi,int n,F f){rep(i,0,n){db l=(lo*2+hi)/3,h=(lo+hi*2)/3;if(f(l)<f(h))lo=l;else hi=h;}return(lo+hi)/2;}

nat sbit(int x){return nat(1)<<x;}
int bit_countl(nat x){return x?__builtin_clzll(x):64;}
int bit_countr(nat x){return x?__builtin_ctzll(x):64;}
int bit_width(nat x){return 64-bit_countl(x);}
int popcount(nat x){return __builtin_popcountll(x);}
tcT T identity(T&&x){return forward<T>(x);}

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
tcF struct yc_result{F f;tcT explicit yc_result(T&&f):f(forward<T>(f)){}tcTs decltype(auto)operator()(Ts&&...ts){return f(ref(*this),forward<Ts>(ts)...);}};
tcF decltype(auto)yc(F&&f){return yc_result<decay_t<F>>(forward<F>(f));}

// https://en.cppreference.com/w/cpp/utility/variant/visit
tcTs struct overloaded:Ts...{using Ts::operator()...;};
tcTs overloaded(Ts...)->overloaded<Ts...>;
template<class T,class...Ts>void match_with(T&&t,Ts&&...fs){visit(overloaded{forward<Ts>(fs)...},forward<T>(t));}
