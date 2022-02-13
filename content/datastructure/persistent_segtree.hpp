template<class M> struct persistent_segtree {
	struct node {
		shared_ptr<node> c[2];
	};

	shared_ptr<node> root;
};
