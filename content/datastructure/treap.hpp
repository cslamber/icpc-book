tcT struct treap {
	using P = unique_ptr<treap>;
	treap* p = nullptr; P l, r;
	size_t s = 1, y; T val;
	treap(T val) : val(val), y(randint(LLONG_MIN, LLONG_MAX)) {}
	void recalc() {
		s = 1; p = nullptr;
		if (l) l->p = this, s += l->s;
		if (r) r->p = this, s += r->s;
	}
	size_t q() const { return l ? l->s : 0; }
	treap* at(size_t i) {
		if (i == q()) return this;
		else if (i < q()) return l->at(i);
		else return r->at(i-1-q());
	}
	pair<treap*,size_t> where(size_t o) {
		if (!p) return {this, o};
		else return p->where(p->r.get() == this ? o+1+p->q() : o);
	}
	auto where() { return where(q()); }
	friend pair<P,P> split(P n, size_t i) {
		if (!n) return {};
		if (n->q() >= i) {
			auto pa = split(move(n->l), i);
			n->l = move(pa.second);
			n->recalc();
			return {move(pa.first), move(n)};
		} else {
			auto pa = split(move(n->r), i-1-n->q());
			n->r = move(pa.first);
			n->recalc();
			return {move(n), move(pa.second)};
		}
	}
	friend P merge(P l, P r) {
		if (!l) return r; if (!r) return l;
		if (l->y > r->y) {
			l->r = merge(move(l->r), move(r));
			l->recalc();
			return l;
		} else {
			r->l = merge(move(l), move(r->l));
			r->recalc();
			return r;
		}
	}
};

tcT struct ptr_store {
	unordered_map<T*, unique_ptr<T>> m;
	void add(unique_ptr<T> p) { m[p.get()] = move(p); }
	template<class...Ts> T* emplace(Ts&&...ts) {
		auto r = make_unique<T>(forward<Ts>(ts)...);
		return (m[r.get()] = move(r)).get();
	}
	unique_ptr<T> take(T* v) {
		auto it = m.find(v);
		auto r = move(it->second);
		m.erase(it);
		return r;
	}
};
