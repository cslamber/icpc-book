/// INCLUDE copy_ptr

tcT struct lichao {
	/* potentially allow fixed precision */
	struct line {
		T m, b;
		T at(ll x) const { return m * x + b; }
	}
	struct node { copy_ptr<node> c[2]; optional<line> line; }
	copy_ptr<node> root;
	ll left, span;
	
	lichao() : root(new line()) {}
};