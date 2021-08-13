template<class T_, class Op>
struct monoid {
    using T = T_;
    T e; Op op;
    monoid(T e, Op op) : e(e), op(op) {}
};

template<class F_, class Mult, class Comp, class Act>
struct monoid_action {
    using F = F_;
    Mult mult; Comp comp; Act act;
    monoid_action(in_place_type_t<F>, Mult mult, Comp comp, Act act) :
        mult(mult), comp(comp), act(act) {}
};
