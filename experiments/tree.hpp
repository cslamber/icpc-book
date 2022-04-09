template<class Elem> struct tree_impl {

struct node; struct tree;
struct node_base {
	node_base *p; node *c[2] = {};
	node_base(node_base *p) : p(p) {}
	bool side() { return p->c[1] == this; }
};
struct node : node_base { Elem data; };

struct iterator {
	node_base *n;
	bool down(bool s) { return n->c[s] && n = n->c[s]; }
	void step(bool s) {
		if (down(s)) while (down(!s));
		else while (exchange(n, n->p)->side() == s);
	}

	bool operator!=(iterator a) const { return n != a.n; }
	iterator& operator++() { step(1); return *this; }
	iterator& operator--() { step(0); return *this; }
	T& operator*() { return static_cast<node*>(n)->data; }
	tree* root() const;
};

struct tree_base : node_base {
	tree_base() : node_base(nullptr) {}
    iterator end() { return this; }
    iterator begin() { auto it = end(); while (it.down(0)); return it; }

	// rule of five
	void reparent_root() { if (c[0]) c[0]->p = this; }
	friend void swap(tree_base& a, tree_base &b) noexcept {
		swap<node_base>(a, b);
		a.reparent_root(); b.reparent_root();
	}

	static node* copy_node(node_base *p, const node* a) {
		if (!a) return;
		node *r = new node; r.p = p;
		rep(i,0,2) c[i] = copy_node(r, a->c[i]);
		return r;
	}
	tree_base(const tree_base& other) : tree_base() { c[0] = copy_node(this, other.c[0]); }
	tree_base(tree_base&& other) noexcept : tree_base() { swap(*this, other); }
	tree_base& operator=(tree_base&& other) noexcept { swap(this, other); return *this; }
	tree_base& operator=(tree_base other) noexcept { swap(*this, other); return *this; }
	~tree_base() {
		iterator it = begin(); bool s;
		while (it.n->p) {
			if (it.down(1)) while (it.down(0));
			else while (s = it.n->side(), delete exchange(it.n, it.n->p), s);
		}
	}
};

template<class Updater> struct tree : tree_base {
	Updater updater;
    tree(Updater upd = Updater()) : updater(upd) {}

	// really a rotate up
    void rotate(node_base *y) {
		bool s = y->side();
		node_base *x = y->p;

		(x->p->c[x->side()] = y)->p = x->p;
		(x->c[s] = y->c[!s])->p = x;
		(y->c[!s] = x)->p = y;

		updater(static_cast<node*>(x));
		updater(static_cast<node*>(y));
    }

	void erase(iterator it) {
		// erase fixup
    }

	void insert(iterator it, T data) {
		node *par = it.node, **ip = &par->c[0];
		while (*ip) par = *ip, ip = par->c[1];
		*ip = new node {par, move(data)};
		// insert fixup
	}

	tree split(iterator it) {

	}

	void join(tree& other) {

	}
};

tree* iterator::root() const {
	auto x = p; while (x->p) x = x->p;
	return static_cast<tree*>(x);
}

};

template<class Elem, class Updater>
using tree = tree_impl<Elem>::tree<Updater>;
