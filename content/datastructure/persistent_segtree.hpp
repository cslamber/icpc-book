template<class G> struct persistent_segtree {
	struct Set { typename G::T v; };
	struct Act { typename G::F v; };
	using action = variant<monostate, Set, Act>;
	using T = G::T;
	struct node {
		shared_ptr<node> c[2];
		T acc; action lazy;
	};
	shared_ptr<node> root;
	G g; ll left, right;

	struct iterator {
		shared_ptr<node>& cur;
		ll left, right;
	};

	T query(ll l, ll r) {
		return dfs([&](auto left, auto right) -> T {
			
		});
	}

	persistent_segtree(G g = G()) : g(g) {}
};
