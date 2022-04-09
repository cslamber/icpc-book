/// INCLUDE match_with

template<class G> struct lazysegtree {
	using T = G::T;
	struct Set { typename G::T v; }
	struct Act { typename G::A v; }
	struct node {
		T acc;
		variant<monostate, Set, Act> lazy;
		node(T a) : acc(a) {}
	};
	G g; uint n;
	vector<node> tree;

	lazysegtree(G g, const vector<T>& base)
			: g(g), n(bit_ceil(sz(base))), tree(2*n, g.e) {
		
	}
};
