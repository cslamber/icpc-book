#ifdef LOCAL
namespace Debug{
bool _DEBUG=1;
template<int N> struct priority_tag : priority_tag<N-1>{};
template<> struct priority_tag<0>{};
struct printer {
    ostream&os;printer(ostream&os):os(os){}
    tcT printer&operator,(const T&t){p(t);return*this;}
    tcT void p(const T&t){p(t,priority_tag<3>());}
    template<class T,class=decltype(os<<declval<T>())>
    void p(const T&t,priority_tag<3>){os<<t;}
    tcT void p(const T&t,priority_tag<0>){
        os<<"[#"<<typeid(T).name()<<"#]";}
    template<class T,class C=typename T::value_type>
    void p(const T&t,priority_tag<2>){
        os<<'{';string sep;
        for(const C&e:t)os<<sep,p(e),sep=", ";
        os<<'}';}
    template<class T,class=decltype(get<0>(declval<T>()))>
    void p(const T&t,priority_tag<1>){
        print_tuple(t,make_index_sequence<tuple_size_v<T>>());}

    template<class Tuple, size_t...I>
    void print_tuple(const Tuple& t, index_sequence<I...>) {
        os<<'{';string sep;
        (...,(os << sep,p(get<I>(t)),sep=", "));
        os<<'}';
    }
};

#define dbg(...) \
    do if (Debug::_DEBUG) { \
        std::cerr << __LINE__ << ": " \
             << "[" << #__VA_ARGS__ \
             << "] = ["; \
        Debug::printer(std::cerr),__VA_ARGS__; \
        std::cerr << "]" << std::endl; \
    } while (0)
#define iflocal if (1)
}
#else
#define dbg(...)
#define iflocal if (0)
#endif
