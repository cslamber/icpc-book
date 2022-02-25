```c++
struct Semigroup {
	struct T { ... };
	T e;
	T op(const T& a, const T& b) const { ... }

	/* for lazy / persisent segtrees */
	struct A { ... };
	void compose(const A& after, A& before) const { ... }
	bool apply(const A& f, T& x, uint doubling) const {
		/* for beats, return if operation was applied to segment, false
		 * splits and continues to apply going down */ }

	bool relevant(const A& f, const T& x, uint doubling) const {
		/* for beats, return if segment is potentially relevant */
		return true; }

	T doubl(T base, uint times) const {
		/* potentially optimize, e.g. (base << times) for sum */
		rep(i,0,times) base = op(base, base);
		return base;
	}
};
```

`segtree` is intentionally very simple and does not support advanced queries unless they can be answered with `.segs()`.  `lazysegtree` should be powerful enough to traversing / dfs and potentially beats. `persistent_segtree` should add sparse and persistence.
