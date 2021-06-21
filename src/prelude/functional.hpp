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

// visit but works with repeated variant types
// NOTE: creates a bunch of if-returns which gcc does not optimize into a jump
// table for large variants
template<size_t I, class Variant, class Fun>
void ordered_visit_(Variant&& v, Fun&& f) {
    //static_assert(I+1 == variant_size_v<Variant>, "");
    f(get<I>(forward<Variant>(v))); }

template<size_t I, class Variant, class Fun, class... Funs>
void ordered_visit_(Variant&& v, Fun&& f, Funs&&... fs) {
    return v.index() == I
        ? f(get<I>(forward<Variant>(v)))
        : ordered_visit_<I+1>(forward<Variant>(v), forward<Funs>(fs)...);
    }

template<class... Args>
void ordered_visit(Args&& ...args) {
    return ordered_visit_<0>(forward<Args>(args)...); }