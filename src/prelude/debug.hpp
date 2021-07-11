namespace Debug {

template<class A,class B>ostream& operator<<(ostream& os,const pair<A,B>& p);

template<class C, class T = enable_if_t<!is_same<C,string>::value, typename C::value_type>>
ostream& operator<<(ostream& os, const C& v){
    os << '{'; string sep;
    for (const T& x: v) os<< sep << x, sep = ", ";
    return os << '}';
}

template<class A,class B>ostream& operator<<(ostream& os, const pair<A,B>& p){
    return os << "{" << p.first << ", " << p.second << "}"; }

template<class H> void Debug(const H& h) {
    cerr << h << "]" << endl; }

template<class H, class...T> void Debug(const H& h, const T&... t) {
    cerr << h << ", "; Debug(t...); }

#ifdef LOCAL
#define dbg(...) cerr << __LINE__ << ": " << "[" << #__VA_ARGS__ << "] = [", Debug::Debug(__VA_ARGS__)
#else
#define dbg(...) 0
#endif
}
