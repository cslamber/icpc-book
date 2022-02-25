template<class G> struct persistent_segtree {
	struct Set { typename G::T v; };
	struct Act { typename G::F v; };
	struct node {
		shared_ptr<node> c[2];
		typename G::T acc;
		variant<monostate, Set, Act> lazy;
	};
	shared_ptr<node> root;
	G g; ll left, right;

	node(G g) : g(g) {}
};
