```c++
struct Monoid {
	struct T { ... };
	T e() const { ... }
	T op(const T& a, const T& b) const { ... }

	// for lazysegtree
	struct A { ... };
	A compose(const A& after, const A& before) const { ... }
	T apply(const A& f, const T& x, size_t doubling) const { ... }
	T double(T base, size_t times) const {
		rep(i,0,times) base = op(base, base);
		return base;
	}

	// might potentially change to
	void apply(const A& f, T& x, size_t doubling) const { ... }
};
```
