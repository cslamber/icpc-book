/// INCLUDE match_with

template<class M> struct lazysegtree {
	struct Set { typename M::T v; }
	struct Act { typename M::A v; }
	struct node {
		typename M::T acc;
		variant<monostate, Set, Act> lazy;
	};
	M m; size_t n;
	vector<node> tree;

	lazysegtree(M m, size_t n)
			: m(m), n(sbit(bit_width(n)))
			, tree(2*n, {M.e(), monostate()}) {
		
	}
};