// CRTP for operations on aggregate types
template<class Par> struct aggregate {
    using A = aggregate;

    bool operator==(const A& a) { return this->tup() == a.tup(); }
    bool operator<(const A& a) { return this->tup() < a.tup(); }
    friend ostream& operator<<(const A& a, ostream& os) { return os << a.tup(); }
};
