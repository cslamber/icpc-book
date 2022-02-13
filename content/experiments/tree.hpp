template<class elem_data, class root_data, class Updater>
struct forest {
	struct node;
	struct node_base { node_base *parent; node *c[2]; };
	struct node : node_base { elem_data data; };
	struct root : node_base { root_data data; };
	struct iterator {
		node_base *n;
		bool down(bool s) { return n->c[s] && n = n->c[s]; }
		void step(bool s) {
			if (down(s)) while (down(!s));
			else for (;;) {
				bool stop = n->parent->c[s] == n;
				n = n->parent;
				if (stop) break;
			}
		}

		bool operator!=(iterator a) const { return n != a.n; }
		iterator& operator++() { step(1); return *this; }
		iterator& operator--() { step(0); return *this; }
		T& operator*() { return static_cast<node*>(n)->data; }
		root* root() const {
			node_base *r = n;
			while (r->parent) r = r->parent;
			return static_cast<root*>(r);
		}
	};

	struct tree {
		root root;
		iterator end() { return &root(); }
		iterator begin() { auto it = end(); while (it.down(0)); return it; }

		tree(root_data data = root_data()) : root {{nullptr}, data}) {}
		tree(const tree& other) : root.data(other.root.data) {
			for (auto& v : other) insert()
		}
		tree(tree&& other) : root.data(move(other.root)) {
			if (root.c[0]) root.c[0]->parent = &root;
			other.root.c[0] = nullptr;
		}
	};

	Updater updater;

	void erase(iterator it) {

	}

	void insert(iterator it, T data) {
		node *par = it.node;
		unique_ptr<node> *ip = &par->c[0];
		while (*ip) par = ip->get(), ip = par->c[1];
		ip->reset(new node {{par}, data});
		/* insert fixup */
	}

	forest(Updater updater = Updater()) : updater(updater) { }
};
